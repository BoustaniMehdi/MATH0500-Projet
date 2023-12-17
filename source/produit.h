/**
 * \file produit.h
 * \brief Header pour les produits de la matrice-matrice et matrice-vecteur
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \date 17/12/2023
 */

/**
 * ALLOCATIONFACTOR
 * 
 * @brief Macro utilisée pour l'allocation de tableau
 */
#define ALLOCATIONFACTOR 2

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
