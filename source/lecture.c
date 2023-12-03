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

Liste *creer_cellule(unsigned int value){
    assert(value >= 0);

    Liste *cellule = malloc(sizeof(Liste));

    if(cellule == NULL)
        return NULL;
    
    cellule->value = value;
    cellule->suivant = NULL;

    return cellule;
}

unsigned int taille_Liste(Liste *L){
    int taille = 0;

    Liste *p = L;

    while(p != NULL){
        taille++;
        p = p->suivant;
    }

    return taille;
}

Liste *add_at(Liste *L, int i, unsigned int value){
    assert(i >= 0 && i < taille_Liste(L) && value >= 0);

    unsigned int j = 0;

    Liste *cellule = creer_cellule(value);

    if(!cellule)
        return L;

    if(i == 0){
        cellule->suivant = L;

        return cellule;
    }

    Liste *p_cour = L;
    Liste *p_prec = NULL;

    while(j < i){
        p_prec = p_cour;
        p_cour = p_cour->suivant;
        j++;
    }

    cellule->suivant = p_cour;
    p_prec->suivant = cellule;

    return L;
}

Liste *add_last(Liste *L, unsigned int value){
    assert(value >= 0);

    Liste *p = L;

    Liste *cellule = creer_cellule(value);

    if(cellule==NULL)
        return L;
    
    if(L == NULL)
        L = cellule;
    else{
        while(p->suivant != NULL)
            p = p->suivant;
        p->suivant = cellule;
    }

    return L;
}



