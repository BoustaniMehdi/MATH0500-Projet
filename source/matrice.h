/**
 * \file lecture.h
 * \brief Header pour la lecture des fichiers d'input et la création de la matrice creuse ou vecteur creux correspondant
 * \author Albashityalshaier Abdelkader, Boustani Mehdi -- Université de Liège (ULiège)
 * \date 17/12/2023
 *
 * Crée une matrice creuse orrespondant au fichier d'input, ainsi la structure de donnée dans laquelle nous stockons celle-ci
 */

#ifndef __MATRICE__
#define __MATRICE__

#include <stdio.h>

/**
 * START
 * 
 * @brief Macro utilisée pour nos opérations sur les indices de nos tableaux.
 */
#define START 1

/**
 * CSC
 * 
 * @brief Structure de données "Compressed Sparse Column" pour la matrice creuse.
 */
typedef struct{
    int *p;
    int *i;
    double *x;
    int nnz;
    int nbRows;
    int nbCols;
}CSC;

/**
 * CSC
 * 
 * @brief Structure de données pour stocker la matrice creuse donnée en input.
 */
typedef struct{
    int *rows;
    int *cols;
    double *values;
}MatrixInput;

/**
 * create_sparse_matrix
 * 
 * @brief Crée une matrice creuse compressée par colonne.
 *
 * @param filename le nom du fichier mtx contenant la matrice creuse
 * 
 * @pre filename != NULL
 *
 * @return CSC *, un pointeur vers notre matrice creuse compressée par colonne.
 *         NULL en cas d'erreur.
 */
CSC *create_sparse_matrix(char *filename);

/**
 * create_input_matrix
 * 
 * @brief Crée une matrice en lisant le fichier mtx.
 *
 * @param filename le nom du fichier mtx contenant la matrice creuse
 * @param FILE *fptr le pointeur du fichier mtx à prendre en compte
 * 
 * @pre matrix != NULL, fptr != NULL
 *
 * @return MatrixInput *, un pointeur vers notre matrice.
 *         NULL en cas d'erreur.
 */
MatrixInput *create_input_matrix(CSC *matrix, FILE *fptr);

/**
 * destroy_matrix
 * 
 * @brief Détruit (free) une matrice creuse compressée par colonne.
 *
 * @param matrix la matrice creuse à détruire
 * 
 * @pre matrix != NULL, matrix->p != NULL, matrix->i != NULL, matrix->x != NULL
 *
 * @return /
 */
void destroy_matrix(CSC *matrix);

/**
 * csc_to_file
 * 
 * @brief Ecrit dans un fichier mtx une matrice creuse compressée par colonne.
 *
 * @param matrix la matrice creuse à afficher
 * @param filename le nom du fichier mtx contenant la matrice creuse
 * 
 * @pre matrix != NULL, matrix->p != NULL, matrix->i != NULL, matrix->x != NULL, filename != NULL
 *
 * @return 1, succès.
 *         0 en cas d'erreur.
 */
unsigned short csc_to_file(CSC *matrix, char *filename);

#endif // __MATRICE__
