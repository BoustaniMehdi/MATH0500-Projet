#ifndef __VALEURPROPRE__
#define __VALEURPROPRE__

#include "lecture.h"

#define MAX_ITER 10000
#define TOLERANCE 0.0001

typedef struct vect {
    int *i;
    double *x;
    int nz;
    int nbLignes;
}vectCreux;


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "valeur_propre.h"

double *mult_mat_vect(CSC *matCreuse, double *vect, int n);

// RENVOIE LA NORME INFINIE D'UN VECTEUR (max component)
double norme(double *vect, int n);

// Generer un vecteur aleatoire
double *generer_vecteur(int n);

unsigned short vect_egaux(double *vect1, double *vect2, int n);

void copier_vecteur(double *source, double *dest, int n);

double *get_vect_propre(CSC *A, double *valPropre);

vectCreux *creer_vecteur_creux(double *vectTableau);


#endif // __VALEURPROPRE__