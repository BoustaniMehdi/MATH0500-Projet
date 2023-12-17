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

    if(strcmp(argv[0], "./multiplication") == 0){
        // NB : Multiplication doit être faite entre une matrice de type A et B 
      
        // MATRICE A
        CSC *A = create_sparse_matrix("matrice.A.mtx"); // Vous pouvez entrer le nom de la matrice A ici
        if (!A){
            printf("Failed to create A \n");
            return 1;
        }
       
        // MATRICE B
        CSC *B = create_sparse_matrix("matrice.B.mtx"); // Vous pouvez entrer le nom de la matrice B ici
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
        char *filename = "produit.mtx";

        unsigned short success = csc_to_file(C, filename);

        if (success){
            printf("A x B was successfully written in %s\n", filename);
        }

        destroy_matrix(A);
        destroy_matrix(B);
        destroy_matrix(C);
    }

     else if (strcmp(argv[0], "./vecteur") == 0){

        // MATRICE A
        CSC *A = create_sparse_matrix("matrice.A.mtx"); // Vous pouvez entrer le nom de la matrice A ici
        if (!A){
            printf("Failed to create matrix\n");
            return 1;
        }

        // Methode de la puissance
        unsigned short convergence = 0;
        unsigned int n = A->nbCols;
        double eigenValue = 0;
        double *eigenVector = get_eigen_vector(A, &eigenValue, &convergence);

        if (!eigenVector){
            printf("Failed to get the dominant eigen value\n");
            destroy_matrix(A);
            return 1;
        }

        if(convergence)
            printf("Dominant eigen value : %lf\n", eigenValue);
        else
            printf("Current dominant eigen value : %lf\n", eigenValue);

        // Transformer le vecteur en vecteur creux
        SparseVector *sparseEigenVector = create_sparse_vector(eigenVector, n);
        if (!sparseEigenVector){
            printf("Failed to create sparse eigen vector\n");
            destroy_matrix(A);
            free(eigenVector);
            return 1;
        }

        // Ecrire le vecteur creux dans un fichier
        vector_to_file(sparseEigenVector, "vecteur.mtx");

        free(eigenVector);

        destroy_vector(sparseEigenVector);
        destroy_matrix(A);
    }

    else{
        printf("Problem while executing the program\n");
    }

    return 0;
}
