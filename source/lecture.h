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

/**
 *\brief Déclaration d'un type opaque pour la structure de données compressed sparse column 
 */
typedef struct csc_t CSC;


int *get_p(CSC *matrice);
int *get_i(CSC *matrice);
int *get_x(CSC *matrice);
int get_nz(CSC *matrice);
int get_nblignes(CSC *matrice);
int get_nbcols(CSC *matrice);


// CSC *init_matrice(int nbLignes, int nbCols, int nz, int *p, int *i, double *x );
CSC *creer_matrice(char *fichierInput);


#endif // __LECTURE__

// VOIR SLIDES CORRECTION TP POUR LE PROJET (SPECIFICATION,INVARIANT,.....)
