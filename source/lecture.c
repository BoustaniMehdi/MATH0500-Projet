/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier lecture.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "lecture.h"

struct csc_t{
    int *p;
    int *i;
    double *x;
    int nz;
    int nbLignes;
    int nbCols;
};

// --------------------------------------- ACCESSEURS -------------------------------------------- //

int *get_p(CSC *matrice){
    assert(matrice != NULL);
    return matrice->p;
}

int *get_i(CSC *matrice){
    assert(matrice != NULL);
    return matrice->i;
}

int *get_x(CSC *matrice){
    assert(matrice != NULL);
    return matrice->x;
}

int get_nz(CSC *matrice){
    assert(matrice != NULL);
    return matrice->nz;
}
int get_nblignes(CSC *matrice){
    assert(matrice != NULL);
    return matrice->nbLignes;
}

int get_nbcols(CSC *matrice){
    assert(matrice != NULL);
    return matrice->nbCols;
}
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
    if(fscanf(fptr, "%d %d %d", &matrice->nbLignes, &matrice->nbCols, &matrice->nz) != 3){
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
    matrice->i = malloc(matrice->nz * sizeof(int));
    if (!matrice->i){
        printf("Erreur creation de la matrice -- array i\n");
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array x (non-nuls). Taille = # non-zeros
    matrice->x = malloc(matrice->nz * sizeof(float)); // float or double?
    if (!matrice->x){
        printf("Erreur creation de la matrice -- array x\n");
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }
    int ligne, col, colCourant = 0, indiceCol = 0;
    float nz;
    // printf("%d\n", indice)
    int indice = 0;
    while (indice < matrice->nz){
        if(fscanf(fptr, "%d %d %f", &ligne, &col, &nz) != 3){
            printf("Erreur lecture : fichier corrompu\n");
            return NULL;
        }
        matrice->x[indice] = nz;
        matrice->i[indice] = ligne;
        if (col != colCourant){
            if (col - colCourant > 1){
                for (int j = 0; j < col-colCourant - 1; j++){
                    matrice->p[indiceCol] = indice + 1;
                    indiceCol++;
                }
            }
            matrice->p[indiceCol] = indice + 1;
            indiceCol++;
            colCourant = col;
        }
        indice ++;
    }
    matrice->p[indiceCol] = indice + 1;
    fclose(fptr);   
    return matrice;
}
