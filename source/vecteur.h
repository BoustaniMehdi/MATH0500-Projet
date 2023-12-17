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
    int size;
}SparseVector;

/**
 * generate_vector
 * 
 * @brief Génère un veteur aléatoire de taille n
 *
 * @param n la taille du veteur à générer
 * 
 * @pre n > 0
 *
 * @return vect, le vecteur aléatoire
 *         NULL en cas d'erreur
 */
double *generate_vector(int n);

/**
 * create_sparse_vector
 * 
 * @brief Transforme un tableau en un vecteur creux compressé par colonne.
 *
 * @param vect le tableau à transformer sous forme de vecteur creux compressé par colonne.
 * 
 * @pre vect != NULL, n > 0
 *
 * @return SparseVector *, un pointeur vers notre vecteur creux compressé par colonne.
 *         NULL en cas d'erreur.
 */
SparseVector *create_sparse_vector(double *vector, unsigned int n);

/**
 * vector_to_file
 * 
 * @brief Ecrit dans un fichier mtx un vecteur creux compressé par colonne.
 *
 * @param vect le vecteur à afficher
 * @param filename le nom du fichier mtx contenant la matrice creuse
 * 
 * @pre vect != NULL, vect->i != NULL, vect->x != NULL, filename != NULL
 *
 * @return 1, succès.
 *         0 en cas d'erreur.
 */
unsigned short vector_to_file(SparseVector *vect, char *filename);

/**
 * destroy_vector
 * 
 * @brief Détruit (free) un vecteur creux creuse compressée par colonne.
 *
 * @param matrix la matrice creuse à détruire
 * 
 * @pre vector != NULL, vector->i != NULL, vector->x != NULL
 *
 * @return /
 */
void destroy_vector(SparseVector *vect);

/**
 * copy_vector
 * 
 * @brief Copie les données d'un vecteur source dans un autre (destination)
 *
 * @param source le vecteur source
 * @param dest le vecteur destination
 * @param n la taille du vecteur à copier
 * 
 * @pre source != NULL, dest != NULL, n > 0
 *
 * @return /
 */
void copy_vector(double *source, double *dest, int n);

/**
 * divide_vect_scalar
 * 
 * @brief Divise un vecteur par un scalaire
 *
 * @param vect le vecteur à diviser
 * @param n la taille du vecteur
 * @param scalar le scalaire utilisé pour la division
 * 
 * @pre vect != NULL, n > 0, scalar != 0
 *
 * @return /
 */
double *divide_vect_scalar(double *vect, int n, double scalar);

/**
 * get_largest_module
 * 
 * @brief Renvoie le plus grand module d'un vecteur donné
 *
 * @param vect le vecteur à diviser
 * @param n la taille du vecteur
 * 
 * @pre vect != NULL, n > 0
 *
 * @return /
 */
double get_largest_module(double *vect, int n);



#endif //__VECTEUR__