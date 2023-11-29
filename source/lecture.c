/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier lecture.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "lecture.h"



// ------------------------------------------------------------------------------------------------ //

// CSC *init_matrice(int nbLignes, int nbCols, int nz, int *p, int *i, double *x ){
//     assert(p != NULL && i != NULL && x != NULL);
//     CSC *matriceCreuse = malloc(sizeof(CSC));
//     if (!matriceCreuse){
//         return NULL;
//     }
//     matriceCreuse->nbLignes = nbLignes;
//     matriceCreuse->nbCols = nbCols;
//     matriceCreuse->nz = nz;
//     matriceCreuse->p = p;
//     matriceCreuse->i = i;
//     matriceCreuse->x = x;
//     return matriceCreuse;
// }

CSC *creer_matrice(char *fichierInput){
    assert(fichierInput != NULL);

    int ligne = 0, col = 0, colCourant = 0, indiceCol = 0, indice = 0;
    float valeur = 0;
    
    CSC *matrice = malloc(sizeof(CSC));
    if (!matrice){
        printf("Erreur creation de la matrice\n");
        return NULL;
    }

    FILE *fptr = fopen(fichierInput, "r");
    if (!fptr){
        printf("Erreur ouverture du fichier input\n");
        free(matrice);
        return NULL;
    }

    if(fscanf(fptr, "%d %d %d", &matrice->nbLignes, &matrice->nbCols, &matrice->nnz) != 3){
        printf("Erreur lecture : fichier corrompu\n");
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array p (colonnes). Taille = # colonnes + 1
    matrice->p = malloc((matrice->nbCols+1) * sizeof(int));
    if (!matrice->p){
        printf("Erreur creation de la matrice -- array p\n");
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array i (lignes). Taille = # non-zeros
    matrice->i = malloc(matrice->nnz * sizeof(int));
    if (!matrice->i){
        printf("Erreur creation de la matrice -- array i\n");
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array x (non-nuls). Taille = # non-zeros
    matrice->x = malloc(matrice->nnz * sizeof(float)); // float or double?
    if (!matrice->x){
        printf("Erreur creation de la matrice -- array x\n");
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    while (indice < matrice->nnz){
        if(fscanf(fptr, "%d %d %f", &ligne, &col, &valeur) != 3){
            printf("Erreur lecture : fichier corrompu\n");
            return NULL;
        }

        matrice->x[indice] = valeur;
        matrice->i[indice] = ligne;

        if (col != colCourant){
            if (col - colCourant > 1){
                for (int j = 0; j < col-colCourant - 1; j++){
                    matrice->p[indiceCol++] = indice + 1;
                }
            }
            matrice->p[indiceCol++] = indice + 1;
            
            colCourant = col;
        }
        indice ++;
    }

    matrice->p[indiceCol] = indice + 1;

    fclose(fptr);   

    return matrice;
}



double *matrice_vecteur(CSC *matCreuse, double *vect, int n){
    assert(matCreuse != NULL && vect != NULL);
    if (matCreuse->nbLignes != n){
        printf("La multiplication n'est pas définie entre la matrice et le vectuer\n");
        return NULL;
    }
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