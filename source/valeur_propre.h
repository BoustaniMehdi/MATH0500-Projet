/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier valeur_propre.h
 */

#include "matrice.h"
#include "vecteur.h"

#ifndef __VALEURPROPRE__
#define __VALEURPROPRE__

#define MAX_ITER 10000
#define TOLERANCE 0.0001



unsigned short vect_egaux(double *vect1, double *vect2, int n);

double *get_vect_propre(CSC *A, double *valPropre);



#endif // __VALEURPROPRE__