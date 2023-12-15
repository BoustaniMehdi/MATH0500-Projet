/**
 * \file produit.h
 * \brief Header pour les produits de la matrice-matrice et matrice-vecteur
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \version 0.1
 * \date 17/12/2023
 *
 * Crée une matrice creuse ou un vecteur creux correspondant au fichier d'input, ainsi la structure de donnée dans laquelle nous stockons ceux-ci
 */

#include "matrice.h"

unsigned int get_nz(int *uni, int size, int *dest, int start);
CSC *produit_matrice_matrice(CSC *A, CSC *B);
double *produit_matrice_vecteur(CSC *matCreuse, double *vect, int n);
