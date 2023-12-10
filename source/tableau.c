/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier tableau.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "tableau.h"

Tableau *realloc_tableau(Tableau *tableau){
    assert(tableau != NULL);

    tableau->capacite *= REALLOC_FACTEUR;
    tableau->valeurs = (double*)realloc(tableau->valeurs, tableau->capacite*sizeof(double));

    return tableau;
}

Tableau *creer_tableau(unsigned int taille){
    assert(taille > 0);

    Tableau *tableau = (Tableau*)malloc(sizeof(Tableau));

    if(!tableau){
        printf("Erreur dans la création du tableau");
        return NULL;
    }

    tableau->capacite = taille;
    tableau->taille = taille;

    tableau->valeurs = (double *)calloc(taille, sizeof(double));

    if(!tableau->valeurs){
        free(tableau);
        return NULL;
    }

    return tableau;
}