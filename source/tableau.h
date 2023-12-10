/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier tableau.h
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef __ARRAY__
#define __ARRAY__

#define REALLOC_FACTEUR 2

typedef struct{
    unsigned int capacite;
    unsigned int taille;
    double *valeurs;
}Tableau;

Tableau *creer_tableau(unsigned int taille);

Tableau *realloc_tableau(Tableau* tableau);

#endif //__ARRAY__