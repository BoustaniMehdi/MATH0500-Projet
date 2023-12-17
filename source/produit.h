/**
 * \file produit.h
 * \brief Header pour les produits de la matrice-matrice et matrice-vecteur
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \version 0.1
 * \date 17/12/2023
 *
 * Crée une matrice creuse ou un vecteur creux correspondant au fichier d'input, ainsi la structure de donnée dans laquelle nous stockons ceux-ci
 */

#define ALLOCATIONFACTOR 3

#include "matrice.h"

CSC *matrix_matrix_product(CSC *A, CSC *B);
void matrix_vector_product(CSC *matrix, double *vect, int n, double *result);
