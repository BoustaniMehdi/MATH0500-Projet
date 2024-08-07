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

/**
 * get_nz
 * 
 * @brief Enlève les duplications des éléments dans uni (= l'union)
 *
 * @param uni l'union des indices de lignes
 * @param size la taille de l'union
 * @param dest le tableau dans lequel nous mettons tous les éléments de l'union sans répétition
 * @param start l'indice par lequel nous commençons à parcourir le tableau dest
 * 
 * @pre uni != NULL, dest != NULL
 *
 * @return nz, le nombre de non-zeros (des éléments sans répétition)
 */
static unsigned int get_nz(int *uni, int size, int *dest, int start);

static unsigned int get_nz(int *uni, int size, int *dest, int start){
    assert(uni != NULL && dest != NULL);

    int nz = 1;

    if (size == 0 || size == 1){
        dest[start] = uni[0];
        return size;
    }

    dest[start] = uni[0];
    
    for (int i = 1; i < size; i++){
        if (uni[i] != uni[i-1]){
            dest[start+nz] = uni[i];
            nz++;
        }
    }

    return nz;
}

CSC *matrix_matrix_product(CSC *A, CSC *B){
    assert(A != NULL && A->p != NULL && A->i != NULL && A->x != NULL && 
           B != NULL && B->p != NULL && B->i != NULL && B->x != NULL);

    if (A->nbCols != B->nbRows){
        printf("Erreur : A x B product is not defined\n");
        return NULL;
    }

    CSC *C = malloc(sizeof(CSC));
    
    if (!C){
        printf("Error : Failed to allocate C\n");
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

    // Taille intititale des tableaux y et tmpI
    unsigned int tmpiSize = A->nnz + B->nnz;
    unsigned int ySize = A->nnz + B->nnz;

    int *uni = malloc(A->nnz * sizeof(int));
    if (!uni){
        printf("Error : Failed to allocate union C\n");
        free(C->p);
        free(C);
        return NULL;
    }

    double *y = malloc(ySize * sizeof(double));
    if (!y){
        free(uni);
        free(C->p);
        free(C);
        printf("Error : Failed to allocate y\n ");
        return NULL;
    }

    double *tmpx = calloc((B->nnz + A->nnz) , sizeof(double));
    if (!tmpx){
        printf("Error : Failed to allocate tmpx\n");
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }

    int *tmpI = malloc(tmpiSize * sizeof(int)); // MAX TAILLE = ?
    if (!tmpI){
        printf("Error : Failed to allocate tmpI\n");
        free(tmpx);
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }

    unsigned int index = 0; // indice pour remplir le tableau temporaire y (pour les non-zeros)
    unsigned int count = 0; // indice pour remplir l'union
    unsigned int nonZeros = 0; // comptage des non-zeros
    unsigned int resZeros = 0; // comptage des zeros resultant du produit
    unsigned int tmpcount = 0; // comtage des zeros resultant du produit a chaque colonne de B
    unsigned int row = 0; // Indice de lignes de C

    for (int j = 0; j < B->nbCols; j++){ // parcourir les colonnes de B
        count = 0;

        for (int k = B->p[j] - START; k <= B->p[j+1] - 1 - START; k++){
            int currCol = B->i[k] - START;

            for (int i = A->p[currCol] - START; i <= A->p[currCol+1] - 1 - START; i++){
                uni[count] = A->i[i];
                tmpx[A->i[i] - START] += B->x[k] * A->x[i];
                count++;
            }
        }

        if (count > 0){
            quickSortIterative(uni, 0, count-1); // trier l'union courante (avec doublons)
        }

        // Verifier si nous avons pas dépassé la taille du tableau
        if (C->nnz + count > tmpiSize){
            tmpiSize *= ALLOCATIONFACTOR;
            tmpI = realloc(tmpI, tmpiSize * sizeof(int));

            if (!tmpI){
                printf("Failed to reallocate tmpI\n");
                free(tmpI);
                free(tmpx);
                free(uni);
                free(y);
                free(C->p);
                free(C);
                return NULL;
            }
        }

        // Nombre d'élements non-nuls dans l'union (sans rep)
        nonZeros = get_nz(uni, count, tmpI, C->nnz);
        tmpcount = 0;

        // Verifier si nous avons pas dépassé la taille du tableau
        if(index + nonZeros > ySize){
            ySize *= ALLOCATIONFACTOR;
            y = realloc(y, ySize * sizeof(double));

            if (!y){
                printf("Failed to reallocate y\n");
                free(y);
                free(tmpI);
                free(tmpx);
                free(y);
                free(C->p);
                free(C);
                return NULL;
            }
        }
        // Remplir un tableau y temporaire pour les non-nuls
        for (unsigned int l = 0; l < nonZeros; l++){
            row = tmpI[l+C->nnz] - START; // ACCEDER LES ELEMENTS POUR EVITER DE TOUT PARCOURIR
            if (tmpx[row] == 0){
                resZeros++;
                tmpcount++;
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
         C->p[j+1] = C->p[j] + nonZeros - tmpcount;
         C->nnz += nonZeros;
    }

    free(uni);
    free(tmpx);

    nonZeros = C->nnz;
    C->nnz -= resZeros;

    index = 0;
    
    // REMPLIR C.i
    C->i = malloc(C->nnz * sizeof(int));
    if(!C->i){
        printf("Error : Failed to allocate C.i\n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C);
        return NULL;
    }

    for (unsigned int j = 0; j < nonZeros; j++){
        if (tmpI[j] != 0){
            C->i[index] = tmpI[j];
            index += 1;
        }
    }

    // REMPLIR C.x
    C->x = malloc(C->nnz * sizeof(double));
    if(!C->x){
        printf("Error : Failed to allocate C.x\n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C->i);
        free(C);
        return NULL;
    }

    index = 0;

    for (int i = 0; i < C->nnz; i++){
        if (y[i] != 0){
            C->x[i] = y[i];
            index += 1;
        }
    }

    free(y);
    free(tmpI);
    return C;
}
// ----------------------------------------------------------------------------------------------------------------- //

void matrix_vector_product(CSC *matrix, double *vect, int n, double *result){
    assert(matrix != NULL && vect != NULL && matrix->nbRows == n && result != NULL);

    for (int i = 0; i < n; i++){
        result[i] = 0;
    }

    for (int i = 0; i < n; i++){
        for (int j = matrix->p[i]-1; j < matrix->p[i+1]-1; j++){
            result[matrix->i[j]-1] += vect[i] * matrix->x[j];
        }
    }
}
