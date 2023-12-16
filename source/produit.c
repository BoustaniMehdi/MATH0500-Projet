/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier produit.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "produit.h"
#include "tri.h"

static unsigned int get_nz(int *uni, int size, int *dest, int start);


static unsigned int get_nz(int *uni, int size, int *dest, int start){
    assert(uni != NULL && dest != NULL);
    if (size == 0 || size == 1){
        dest[start] = uni[0];
        return size;
    }
    dest[start] = uni[0];
    int nz = 1;
    for (int i = 1; i < size; i++){
        if (uni[i] != uni[i-1]){
            dest[start+nz] = uni[i];
            nz++;
        }
    }
    return nz;
}

// Changment : Ne pas prendre en compte les zeros du produit
CSC *matrix_matrix_product(CSC *A, CSC *B){
    assert(A != NULL && A->p != NULL && A->x != NULL && A->i != NULL  
        && B != NULL && B->p != NULL && B->x != NULL && B->i != NULL);

    if (A->nbCols != B->nbRows){
        printf("Error : The product A x B is not defined\n");
        return NULL;
    }
    CSC *C = malloc(sizeof(CSC));
    if (!C){
        printf("Error : Failed to allocate C = (A x B) \n");
        return NULL;
    }    
    C->p = malloc((B->nbCols +1) * sizeof(int));
    if (!C->p){
        printf("Error : Failed to allocate C.p\n");
        free(C);
        return NULL;
    }
    C->p[0] = START;
    C->nbRows = A->nbRows;
    C->nbCols = B->nbCols;
    C->nnz = 0;
        
    int *uni = malloc(A->nnz * sizeof(int));
    if (!uni){
        printf("Error : Failed to allocate rows union for product\n");
        free(C->p);
        free(C);
        return NULL;
    }
    
    double *y = malloc((B->nnz + A->nnz) * sizeof(double));
    if (!y){
        free(uni);
        free(C->p);
        free(C);
        printf("Error : Failed to allocate y : non-zeros storage for C.x\n ");
        return NULL;
    }

    double *tmpx = calloc((B->nnz + A->nnz), sizeof(double));
    if (!tmpx){
        printf("Error : Failed to allocate tmpx \n");
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }

    int *tmpI = malloc((B->nnz + A->nnz) * sizeof(int)); // MAX TAILLE = ?
    if (!tmpI){
        printf("Error : Failed to allocate tmpI : rows storage for C.i \n");
        free(tmpx);
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }
    unsigned int index = 0; // indice pour remplir les tableaux C.i et C.x
    unsigned int count = 0; // indice pour remplir l'union 
    unsigned int nonZeros = 0; // comptage des non-zeros
    unsigned int resZeros = 0; // compte le nombre de zeros total resultant du produit
    unsigned int tmpcount = 0; // compte le nombre de zeros resultant du produit pour chaque colonne (pour mettre à jour C.p)
    for (int j = 0; j < B->nbCols; j++){ // parcourir les colonnes de B
        count = 0;
        for (int k = B->p[j] - START; k <= B->p[j+1] - 1 - START; k++){ // identifier les non-zeros de B
            int currCol = B->i[k] - START;
            for (int i = A->p[currCol] - START; i <= A->p[currCol+1] - 1 - START; i++){
                uni[count] = A->i[i];   // ajouter à l union l indice de ligne correspondant au non zero de b
                tmpx[A->i[i] - START] += B->x[k] * A->x[i]; // effectuer le calcul
                count++;
            }
        }
        if (count > 0){
            quickSortIterative(uni, 0, count-1); // trier l'union courante (avec doublons)
        }
        // Nombre des elements non-nuls dans l'union (sans rep)
        nonZeros = get_nz(uni, count, tmpI, C->nnz);
        tmpcount = 0;
        // Remplir un tableau y temporaire pour les non-nuls
        for (int l = 0; l < nonZeros; l++){
            unsigned int row = tmpI[l+C->nnz] - START; // ACCEDER LES ELEMENTS POUR EVITER DE TOUT PARCOURIR
            if (tmpx[row] == 0){
                // printf("%d\n", resZeros);
                resZeros += 1;
                tmpcount += 1;
                tmpI[l+C->nnz] = 0; 
                y[index] = 0;
            }
            else {

                y[index] = tmpx[row];
                index += 1;    
            }
            tmpx[row] = 0;
            
        }
        // mettre a jour C.p et C.nz
         C->p[j+1] = C->p[j] + nonZeros - tmpcount; // retirer le nombre de non-zeros trouvé dans la colonne courante
         C->nnz += nonZeros; // compté avec les zéros du résultats
    }
    nonZeros = C->nnz;
    C->nnz -= resZeros; // compté sans les zéros du résultats

    free(uni);
    free(tmpx);
    
    // Remplir C.i
    C->i = malloc(C->nnz * sizeof(int));
    if(!C->i){
        printf("Error : Failed to allocate C.i \n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C);
        return NULL;
    }
    index = 0;
    for(int j = 0; j < A->nnz + B->nnz; j++){
        if (tmpI[j] != 0){
            C->i[index] = tmpI[j];
            index += 1;
        }
    }
    free(tmpI);

    // Remplir C.x
    C->x = malloc(C->nnz * sizeof(double));
    if(!C->x){
        printf("Error : Failed to allocate C.x \n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C->i);
        free(C);
        return NULL;
    }
    index = 0;
    for (int i = 0; i < nonZeros; i++){
        if (y[i] != 0){
            C->x[index] = y[i];
            index += 1;
        }
    }
    free(y);
    return C;
}

void matrix_vector_product(CSC *matrix, double *vect, int n, double *result){
    assert(matrix != NULL && vect != NULL && matrix->nbRows == n);
    for (int i = 0; i < n; i++){
        result[i] = 0;
    }
    for (int i = 0; i < n; i++){
        for (int j = matrix->p[i]-1; j < matrix->p[i+1]-1; j++){
            result[matrix->i[j]-1] += vect[i] * matrix->x[j]; 
        }
    }
}
