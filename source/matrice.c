/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier matrice.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "matrice.h"


// ------------------------------------------------------------------------------------------------ //

CSC *creer_matrice(char *fichierInput){
    assert(fichierInput != NULL);

    int ligne = 0, col = 0, colCourant = 0, indiceCol = 0, indice = 0;
    double valeur = 0;
    
    CSC *matrice = malloc(sizeof(CSC));
    if (!matrice){
        printf("Erreur creation de la matrice\n");
        return NULL;
    }

    FILE *fptr = fopen(fichierInput, "r");
    if(!fptr){
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
    matrice->x = malloc(matrice->nnz * sizeof(double));
    if (!matrice->x){
        printf("Erreur creation de la matrice -- array x\n");
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    while(indice < matrice->nnz){

        if(fscanf(fptr, "%d %d %lf", &ligne, &col, &valeur) != 3){
            printf("Erreur lecture : fichier corrompu\n");
            return NULL;
        }

        matrice->x[indice] = valeur;
        matrice->i[indice] = ligne;

        if(col != colCourant){

            if(col - colCourant > 1){
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



