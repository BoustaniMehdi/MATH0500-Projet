/*
 * Auteurs : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liege
 * Projet de programmation MATH0500
 * Fichier lecture.h
 */

#ifndef __LECTURE__
#define __LECTURE__

/**
 * \file lecture.h
 * \brief Header pour la lecture des fichiers d'input et la création de la matrice creuse ou vecteur creux correspondant
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \version 0.1
 * \date 17/12/2023
 *
 * Crée une matrice creuse ou un vecteur creux correspondant au fichier d'input, ainsi la structure de donnée dans laquelle nous stockons ceux-ci
 */


typedef struct{
    int *p;
    int *i;
    double *x;
    int nnz;
    int nbLignes;
    int nbCols;
}CSC;


// CSC *init_matrice(int nbLignes, int nbCols, int nz, int *p, int *i, double *x );
CSC *creer_matrice(char *fichierInput);


#endif // __LECTURE__

// VOIR SLIDES CORRECTION TP POUR LE PROJET (SPECIFICATION,INVARIANT,.....)
