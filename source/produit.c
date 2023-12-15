/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier produit.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "produit.h"
#include "tableau.h"
#include "tri.h"


// -------------------------------------------- NOUVEAU PRODUIT ------------------------------------------------------ // 

CSC *produit_matrice_matrice(CSC *A, CSC *B){
    assert(A != NULL && B != NULL);
    if (A->nbCols != B->nbLignes){
        printf("Erreur : Le produit AxB n'est pas definie\n");
        return NULL;
    }
    CSC *C = malloc(sizeof(CSC));
    if (!C){
        printf("Erreur : Echec d'allocation de la matrice C\n");
        return NULL;
    }    
    C->p = malloc((B->nbCols +1) * sizeof(int));
    if (!C->p){
        printf("Erreur : Echec d'allocation de C.p\n");
        free(C);
        return NULL;
    }
    C->p[0] = DEBUT;
    C->nbLignes = A->nbLignes;
    C->nbCols = B->nbCols;
    C->nnz = 0;
        
    int *uni = malloc(A->nnz * sizeof(int));
    if (!uni){
        printf("Erreur : Echec d'allocation pour l'union\n");
        free(C->p);
        free(C);
        return NULL;
    }
    
    double *y = malloc((B->nnz + A->nnz) * sizeof(double));
    if (!y){
        free(uni);
        free(C->p);
        free(C);
        printf("Erreur : Echec d'allocation pour y (= resultat matrice vecteur)\n ");
        return NULL;
    }

    double *tmpx = calloc((B->nnz + A->nnz), sizeof(double));
    if (!tmpx){
        printf("Erreur : Echec d'allocation pour tmpx (= resultat matrice vecteur)\n");
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }

    int *tmpI = malloc((B->nnz + A->nnz) * sizeof(int)); // MAX TAILLE = ?
    if (!tmpI){
        printf("Erreur : Echec d'allocation pour tmpI\n");
        free(tmpx);
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }
    unsigned int idx = 0; // indice pour remplir le tableau temporaire y (pour les non-zeros)
    unsigned int count = 0; // indice pour remplir l'union
    unsigned int nonZeros = 0; // comptage des non-zeros
    unsigned int resZeros = 0; // compte le nombre de zeros resultant du produit
    unsigned int tmpcount = 0;
    for (int j = 0; j < B->nbCols; j++){ // parcourir les colonnes de B
        count = 0;
        for (int k = B->p[j] - DEBUT; k <= B->p[j+1] - 1 - DEBUT; k++){ // identifier les non-zeros de B
            int currCol = B->i[k] - DEBUT;
            for (int i = A->p[currCol] - DEBUT; i <= A->p[currCol+1] - 1 - DEBUT; i++){
                uni[count] = A->i[i];   // ajouter à l union l indice de ligne correspondant au non zero de b
                tmpx[A->i[i] - DEBUT] += B->x[k] * A->x[i]; // effectuer le calcul
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
            unsigned int ligne = tmpI[l+C->nnz] - DEBUT; // ACCEDER LES ELEMENTS POUR EVITER DE TOUT PARCOURIR
            if (tmpx[ligne] == 0){
                resZeros += 1;
                tmpcount += 1;
                tmpI[l+C->nnz] = 0; 
                y[idx] = 0;
            }
            else {
                y[idx] = tmpx[ligne];
                idx += 1;    
            }
            tmpx[ligne] = 0;
            
        }
        // mettre a jour C.p et C.nz
         C->p[j+1] = C->p[j] + nonZeros - tmpcount; // retirer le nombre de non-zeros trouvé dans la colonne courante
         C->nnz += nonZeros; // compté avec les zéros du résultats
    }
    nonZeros = C->nnz;
    C->nnz -= resZeros; // compté sans les zéros du résultats

    free(uni);
    free(tmpx);
    
    C->i = malloc(C->nnz * sizeof(int));
    if(!C->i){
        printf("Erreur : Echec d'allocation de C.i \n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C);
        return NULL;
    }
    
    C->x = malloc(C->nnz * sizeof(double));
    if(!C->x){
        printf("Erreur : Echec d'allocation de C.i \n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C->i);
        free(C);
        return NULL;
    }
    // REMPLIR C.i et C.x
    idx = 0;
    for (int j = 0; j < nonZeros; j++){
        if (tmpI[j] != 0 && y[j] != 0){
            C->x[idx] = y[j];
            C->i[idx] = tmpI[j];
            idx += 1;
        }
    }

    free(y);
    free(tmpI);
    return C;
}

// --------------------------------------------------------------------------------------------------------------------// 


// ----------------------------------------------------------------------------------------------------------------- //

unsigned int get_nz(int *uni, int size, int *dest, int start){
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

CSC *produit_matrice_matrice(CSC *A, CSC *B){
    assert(A != NULL && A->p != NULL && A->i != NULL && A->x != NULL && 
           B != NULL && B->p != NULL && B->i != NULL && B->x != NULL);

    if (A->nbCols != B->nbLignes){
        printf("Erreur : Le produit AxB n'est pas definie\n");
        return NULL;
    }

    CSC *C = malloc(sizeof(CSC));
    if (!C){
        printf("Erreur : Echec d'allocation de la matrice C\n");
        return NULL;
    }    

    C->p = malloc((B->nbCols +1) * sizeof(int));
    if (!C->p){
        printf("Erreur : Echec d'allocation de C.p\n");
        free(C);
        return NULL;
    }

    C->p[0] = DEBUT;
    C->nbLignes = A->nbLignes;
    C->nbCols = B->nbCols;
    C->nnz = 0;
        
    int *uni = malloc(A->nnz * sizeof(int));
    if (!uni){
        printf("Erreur : Echec d'allocation pour l'union\n");
        free(C->p);
        free(C);
        return NULL;
    }
    
    double *y = malloc((B->nnz + A->nnz) * sizeof(double));
    if (!y){
        free(uni);
        free(C->p);
        free(C);
        printf("Erreur : Echec d'allocation pour y (= resultat matrice vecteur)\n ");
        return NULL;
    }

    double *tmpx = calloc((B->nnz + A->nnz), sizeof(double));
    if (!tmpx){
        printf("Erreur : Echec d'allocation pour tmpx (= resultat matrice vecteur)\n");
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }

    int *tmpI = malloc((B->nnz + A->nnz) * sizeof(int)); // MAX TAILLE = ?
    if (!tmpI){
        printf("Erreur : Echec d'allocation pour tmpI\n");
        free(tmpx);
        free(uni);
        free(y);
        free(C->p);
        free(C);
        return NULL;
    }
    unsigned int idx = 0; // indice pour remplir le tableau temporaire y (pour les non-zeros)
    unsigned int count = 0; // indice pour remplir l'union
    unsigned int nonZeros = 0; // comptage des non-zeros
    
    for (int j = 0; j < B->nbCols; j++){ // parcourir les colonnes de B
        count = 0;
        for (int k = B->p[j] - DEBUT; k <= B->p[j+1] - 1 - DEBUT; k++){ // identifier les non-zeros de B
            int currCol = B->i[k] - DEBUT;
            for (int i = A->p[currCol] - DEBUT; i <= A->p[currCol+1] - 1 - DEBUT; i++){
                uni[count] = A->i[i];   // ajouter à l union l indice de ligne correspondant au non zero de b
                tmpx[A->i[i] - DEBUT] += B->x[k] * A->x[i]; // effectuer le calcul
                count++;
            }
        }
        if (count > 0){
            quickSortIterative(uni, 0, count-1); // trier l'union courante (avec doublons)
        }
        // Nombre des elements non-nuls dans l'union (sans rep)
        nonZeros = get_nz(uni, count, tmpI, C->nnz);
        // Remplir un tableau y temporaire pour les non-nuls
        for (unsigned int l = 0; l < nonZeros; l++){
            unsigned int ligne = tmpI[l+C->nnz] - DEBUT; // ACCEDER LES ELEMENTS POUR EVITER DE TOUT PARCOURIR
                y[idx] = tmpx[ligne];
                idx += 1;
                tmpx[ligne] = 0;
        }
        // mettre a jour C.p et C.nz
         C->p[j+1] = C->p[j] + nonZeros;
         C->nnz += nonZeros;
    }
    free(uni);
    free(tmpx);
    
    C->i = malloc(C->nnz * sizeof(int));
    if(!C->i){
        printf("Erreur : Echec d'allocation de C.i \n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C);
        return NULL;
    }
    
    C->x = malloc(C->nnz * sizeof(double));
    if(!C->x){
        printf("Erreur : Echec d'allocation de C.i \n");
        free(y);
        free(tmpI);
        free(C->p);
        free(C->i);
        free(C);
        return NULL;
    }
    // REMPLIR C.i et C.x
    for (int j = 0; j < C->nnz; j++){
        C->x[j] = y[j];
        C->i[j] = tmpI[j];
    }

    free(y);
    free(tmpI);
    return C;
}

// ----------------------------------------------------------------------------------------------------------------- //

double *produit_matrice_vecteur(CSC *matCreuse, double *vect, int n){
    assert(matCreuse != NULL && matCreuse->i != NULL && matCreuse->p != NULL && vect != NULL && matCreuse->nbLignes == n);

    // le vecteur produit on initialise tout à 0
    double *y = calloc(n, sizeof(double));

    if (!y){
        printf("Echec du produit MATRICE x VECTEUR : Allocation du vecteur produit échouée\n");
        return NULL;
    }
    // ----------------------------------Indexing starting at 0 ------------------------------------- //
    // for (int i = 0; i < n; i++){
    //     for (int j = matCreuse->p[i]; j <= matCreuse->p[i+1]-1; j++){
    //         y[matCreuse->i[j]] += vect[i] * matCreuse->x[j]; 
    //     }
    // }

    // ----------------------------------Indexing starting at 1 ------------------------------------- //
    for (int i = 0; i < n; i++){ // parcourt les colonnes du vecteur
        for (int j = matCreuse->p[i]-1; j < matCreuse->p[i+1]-1; j++){ // parcourt la colonne i
            y[matCreuse->i[j]-1] += vect[i] * matCreuse->x[j]; 
        }
    }
    return y;
}