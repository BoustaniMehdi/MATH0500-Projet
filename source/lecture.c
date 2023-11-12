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
    fscanf(fptr, "%d %d %d", &matrice->nbLignes, &matrice->nbCols, &matrice->nz);

    // Initialisation array p (colonnes). Taille = # colonnes + 1
    matrice->p = malloc((matrice->nbCols+1) * sizeof(int));
    if (!matrice->p){
        free(matrice);
        fclose(fptr);
        printf("Erreur creation de la matrice -- array p\n");
        return NULL;
    }

    // Initialisation array i (lignes). Taille = # non-zeros
    matrice->i = malloc(matrice->nz * sizeof(int));
    if (!matrice->i){
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        printf("Erreur creation de la matrice -- array i\n");
        return NULL;
    }

    // Initialisation array x (non-nuls). Taille = # non-zeros
    matrice->x = malloc(matrice->nz * sizeof(double));
    if (!matrice->x){
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        printf("Erreur creation de la matrice -- array x\n");
        return NULL;
    }
    // TODO (lire le fichier et construire les arrays)
}
