/**
 * \file lecture.h
 * \brief Header pour la lecture des fichiers d'input et la création de la matrice creuse ou vecteur creux correspondant
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \version 0.1
 * \date 17/12/2023
 *
 * Crée une matrice creuse ou un vecteur creux correspondant au fichier d'input, ainsi la structure de donnée dans laquelle nous stockons ceux-ci
 */

#ifndef __LECTURE__
#define __LECTURE__

typedef struct ListeCell{
    unsigned int value;
    struct ListeCell *suivant;
}Liste;

typedef struct{
    Liste *p;
    Liste *i;
    Liste *x;
}CSCListe;

typedef struct{
    int *p;
    int *i;
    double *x;
    int nnz;
    int nbLignes;
    int nbCols;
}CSC;

typedef struct{
    int *i;
    double *x;
    int nnz;
    int taille;
}vectCreux;

CSC *creer_matrice(char *fichierInput);

Liste *creer_cellule(unsigned int value);

Liste *add_at(Liste *L, int i, unsigned int value);

Liste *add_last(Liste *L, unsigned int value);

unsigned int taille_Liste(Liste *L);


#endif // __LECTURE__

// VOIR SLIDES CORRECTION TP POUR LE PROJET (SPECIFICATION,INVARIANT,.....)
