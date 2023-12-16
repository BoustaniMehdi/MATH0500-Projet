/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier valeur_propre.h
 */

#include "matrice.h"
#include "vecteur.h"

#ifndef __VALEURPROPRE__
#define __VALEURPROPRE__

#define MAX_ITER 10000 // Nombre d'itérations pour la méthode de puissance
#define TOLERANCE 1e-4 // Tolérance pour vérifier si deux vecteurs sont égaux

/**
 * are_equal
 * 
 * @brief Vérifie si deux vecteurs donnés sont égaux ou non
 *
 * @param vect1 le premier vecteur
 * @param vect2 le deuxième vecteur
 * @param n la taille des vecteurs
 * 
 * @pre vect1 != NULL, vect2 != NULL, n > 0
 *
 * @return 1 si les deux vecteurs sont égaux.
 *         0 sinon.
 */
unsigned short are_equal(double *vect1, double *vect2, int n);

/**
 * get_eigen_vector
 * 
 * @brief Calcule le veteur propre d'une matrice creuse à l'aide de la méthode puissance
 *
 * @param A la matrice creuse
 * @param eigenValue la valeur propre de la matrice A
 * 
 * @pre A != NULL, A->p != NULL, A->i != NULL, A->x != NULL, eigenValue != NULL
 *
 * @return le vecteur propre associé à la valeur propre de A si la méthode de puissance a convergé.
 *         NULL en cas d'erreur.
 */
double *get_eigen_vector(CSC *A, double *eigenValue);



#endif // __VALEURPROPRE__