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
#define TOLERANCE 1e-4


unsigned short are_equal(double *vect1, double *vect2, int n);

double *get_eigen_vector(CSC *A, double *eigenValue);



#endif // __VALEURPROPRE__