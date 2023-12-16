/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier vecteur.h
 */

#ifndef __VECTEUR__
#define __VECTEUR__

#define TOLVECT 1e-10


typedef struct{
    int *i;
    double *x;
    int nnz;
    int size;
}sparseVector;


sparseVector *create_sparse_vector(double *vector, unsigned int n);
unsigned short vector_to_file(sparseVector *vect, char *filename);
void destroy_vector(sparseVector *vect);

double *generate_vector(int n);
void copy_vector(double *source, double *dest, int n);
double *divide_vect_scalar(double *vect, int n, double scalar);

// RENVOIE LA NORME INFINIE D'UN VECTEUR (max component)
double get_largest_module(double *vect, int n);



#endif //__VECTEUR__