/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier vecteur.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "vecteur.h"


double *generer_vecteur(int n){
    assert(n > 0);
    
    double *vect = malloc(n * sizeof(double));

    if (!vect){
        printf("Erreur : Echec allocation -- Echec generation du vecteur\n");
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++){
        vect[i] = (double)rand() / RAND_MAX;
    }
       
    return vect;
}

void copier_vecteur(double *source, double *dest, int n){
    assert(source != NULL && dest != NULL && n > 0);

    for (int i = 0; i < n; i++){
        dest[i] = source[i];
    }
}