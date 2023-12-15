/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier vecteur.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "vecteur.h"

// ---------------------------------------- CHANGEMENTS ------------------------------------------------------ //
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

// Changement : Enlever les nombres TRES proche de 0 (à une TOLVECT pres)
vectCreux *creer_vecteur_creux(double *vectTableau, unsigned int n){
    assert(vectTableau != NULL);

    vectCreux *vect = malloc(sizeof(vectCreux));
    if (!vect){
        printf("Erreur : Echec creation du vecteur creux\n");
        return NULL;
    }

    unsigned int nonZeros = 0;
    // size_t n = sizeof(vectTableau);
    vect->taille = n;

    for (unsigned int i = 0; i < n; i++){
        if ( fabs(vectTableau[i]) > TOLVECT && vectTableau[i] != 0 ){
            nonZeros += 1;
        }
    }

    vect->nnz = nonZeros;
    vect->i = malloc(nonZeros * sizeof(int));
    if (!vect->i){
        free(vect);
        printf("Erreur : Echec allocation vecteur creux\n");
        return NULL;
    }

    vect->x = malloc(nonZeros * sizeof(double));
    if (!vect->x){
        free(vect->i);
        free(vect);
        printf("Erreur : Echec allocation vecteur creux\n");
        return NULL;
    }

    unsigned int indice = 0;
    for (unsigned int j = 0; j < n; j++){
        if(fabs(vectTableau[j]) > TOLVECT && vectTableau[j] != 0){
            vect->x[indice] = vectTableau[j];
            vect->i[indice] = j;
            indice++;
        }
    }

    return vect;
}


// ------------------------------------------------------------------------------------------- //

void copier_vecteur(double *source, double *dest, int n){
    assert(source != NULL && dest != NULL && n > 0);

    for (int i = 0; i < n; i++){
        dest[i] = source[i];
    }
}

double *diviser_vect_scalaire(double *vect, int n, double scalaire){
    assert(vect != NULL);
    for (int i = 0; i < n; i++){
        vect[i] /= scalaire;
    }
    return vect;
}


// RENVOIE LA NORME INFINIE D'UN VECTEUR (max component)
double norme_infinie(double *vect, int n){ 
    assert(vect != NULL && n > 0);

    double max = fabs(vect[0]);

    for(int i = 1; i < n; i++){
        if(fabs(vect[i]) > max){
            max = fabs(vect[i]);
        }
    }

    return max;
}

// Changement : prendre la valeur reelle et non la valeur absolue
double norme(double *vect, int n){ // norme 0 = nnz
    assert(vect != NULL);

    double max = fabs(vect[0]); 

    for (int i = 1; i < n; i++){
        if (fabs(vect[i]) > fabs(max)){ // CHANGEMENT ICI : ON COMPARE LA VALEUR ABSOLUE MAIS ON PREND LA VALEUR REELLE
            max = (vect[i]);
        }
    }

    return max;
}
