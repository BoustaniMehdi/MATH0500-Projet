/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier vecteur.h
 */

#ifndef __VECTEUR__
#define __VECTEUR__

typedef struct{
    int *i;
    double *x;
    int nnz;
    int taille;
}vectCreux;

double *generer_vecteur(int n);

void copier_vecteur(double *source, double *dest, int n);

#endif //__VECTEUR__