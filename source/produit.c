/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier produit.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "produit.h"
#include "lecture.h"

double *matrice_vecteur(CSC *matCreuse, double *vect){
    assert(matCreuse != NULL && vect != NULL && matCreuse->nbLignes == sizeof(vect));

    // le vecteur produit on initialise tout à 0
    double *y = calloc(matCreuse->nbLignes, sizeof(double));

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
    for (int i = 0; i < matCreuse->nbLignes; i++){ // parcourt les colonnes du vecteur
        for (int j = matCreuse->p[i]-1; j < matCreuse->p[i+1]-1; j++){ // parcourt la colonne i
            y[matCreuse->i[j]-1] += vect[i] * matCreuse->x[j]; 
        }
    }
    return y;
}

CSC *matrice_matrice(CSC *A, CSC *B){
    assert(A != NULL && B != NULL && A->nbCols == B->nbLignes);

    int elements = 0;

    CSCListe *C = malloc(sizeof(CSCListe));

    if(!C){
        printf("Erreur creation de la matrice\n");
        return NULL;
    }

    C->p = NULL;
    C->i = NULL;
    C->x = NULL;

    unsigned int count = 0;

    for(unsigned int j = 0; j < B->nbCols; j++){
        //On verifie si on est pas sur une colonne vide
        if(B->p[j] != B->p[j+1]){
            elements = 0;

            for(unsigned int k = B->p[j]; k < B->p[j+1]; k++){
                for(unsigned int i = A->p[B->i[k]]; i < A->p[B->i[k]+1]; i++){
                    add_last(C->p, A->i[i]); //Ca marche pour l'exemple du cours mais faut faire l'union
                    add_at(C->x, i, A->x[i] * B->x[k]); //L'indice i du résultat est incorrecte, à corriger
                    elements++;
                }
            }  

        }

        add_at(C->p, j, elements);
    }
}