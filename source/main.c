/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier main.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "produit.h"

int main(int argc, char *argv[]){

    if (argc < 1) {
        printf("Problème lors de l'exécution du programme\n");
        return 1;
    }

    if(strcmp(argv[0], "./produit") == 0){
        // MATRICE A 
        CSC *A = create_sparse_matrix("cont1.A.mtx");
        if (!A){
            printf("Failed to create A \n");
            return 1;
        }

        // MATRICE B
        CSC *B = create_sparse_matrix("cont1.A.mtx");
        if (!B){
            printf("Failed to create B\n");
            destroy_matrix(A);
            return 1;
        }

        // Produit A x B
        CSC *C = matrix_matrix_product(A, B);
        if (!C){
            printf("Product A x B failed\n");
            destroy_matrix(A);
            destroy_matrix(B);
            return 1;
        }

        // Ecriture de C dans un fichier
        csc_to_file(C, "brand.C.mtx");

        destroy_matrix(A);
        destroy_matrix(B);
        destroy_matrix(C);
    }

    else if (strcmp(argv[0], "./puissance") == 0){
        printf("cc");
        // MATRICE A
        CSC *A = create_sparse_matrix("Matrices/brand.A.mtx");
        if (!A){
            printf("Failed to create matrix\n");
            return 1;
        }
        // Methode de la puissance
        unsigned int n = A->nbCols;
        double eigenValue = 0;
        double *eigenVector = get_eigen_vector(A, &eigenValue);
        if (!eigenVector){
            printf("Failed to get the dominant eigen value\n");
            destroy_matrix(A);
            return 1;
        }
        printf("Dominant eigen value : %lf\n", eigenValue);

        // Transformer le vecteur en vecteur creux
        SparseVector *sparseEigenVector = create_sparse_vector(eigenVector, n);
        if (!sparseEigenVector){
            printf("Failed to create sparse eigen vector\n");
            destroy_matrix(A);
            free(eigenVector);
            return 1;
        }

        // Ecrire le vecteur creux dans un fichier
        vector_to_file(sparseEigenVector, "brandeigen.A.mtx");

        free(eigenVector);
        destroy_vector(sparseEigenVector);
        destroy_matrix(A);
    }

    else{
        printf("Problème lors de l'exécution du programme\n");
    }

    return 0;
}