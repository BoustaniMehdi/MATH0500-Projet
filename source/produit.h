/**
 * \file produit.h
 * \brief Header pour les produits de la matrice-matrice et matrice-vecteur
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \version 0.1
 * \date 17/12/2023
 *
 * Crée une matrice creuse correspondant au fichier d'input, ainsi la structure de donnée dans laquelle nous stockons ceux-ci
 */

#define ALLOCATIONFACTOR 3

#include "valeur_propre.h"

/**
 * matrix_matrix_product
 * 
 * @brief Calcule le produit de deux matrices creuses
 *
 * @param A la première matrice creuse
 * @param B la deuxème matrice creuse
 *
 * @return CSC *C, le résultat du produit A*B
 */
CSC *matrix_matrix_product(CSC *A, CSC *B);

/**
 * matrix_vector_product
 * 
 * @brief Calcule le produit d'une matrice creuse avec un vecteur
 *
 * @param matrix la matrice creuse
 * @param vect le vecteur
 * @param n la taille du vecteur
 * @param result le résultat du produit étant un vecteur
 *
 * @return /
 */
void matrix_vector_product(CSC *matrix, double *vect, int n, double *result);
