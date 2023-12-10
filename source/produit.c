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

CSC *matrice_matrice(CSC *A, CSC *B){
    assert(A != NULL && B != NULL && A->nbCols == B->nbLignes);

    unsigned int elements = 0, indice = 0;

    CSC *C = malloc(sizeof(CSC));

    if(!C){
        printf("Erreur creation de la matrice\n");
        return NULL;
    }

    //A corriger version tableau
    C->p = creer_tableau();
    C->i = NULL;
    C->x = NULL;

    for(unsigned int j = 0; j < B->nbCols; j++){
        
        //On verifie si on est pas sur une colonne vide
        if(B->p[j] != B->p[j+1]){
            elements = 0;

            for(unsigned int k = B->p[j]; k < B->p[j+1]; k++){
                for(unsigned int i = A->p[B->i[k]]; i < A->p[B->i[k]+1]; i++){
                    C->p[indice] = A->i[i]; //Ca marche pour l'exemple du cours mais faut faire l'union
                    C->x[i] = A->x[i] * B->x[k]; //L'indice i du résultat est incorrecte, à corriger
                    elements++;
                }
            }  

        }

        C->p[j] = elements;
    }
}

double *matrice_vecteur(CSC *matCreuse, double *vect, int n){
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