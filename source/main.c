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
        // ------------------------------------------ TEST TOUTES MATRICES ----------------------------------------------- // 

        //   char *filesA[] = {"Matrices/brand.A.mtx",  "Matrices/brandy.A.mtx", "Matrices/buildingenergy.A.mtx",
        //                   "Matrices/cont1.A.mtx",  "Matrices/cont4.A.mtx",  "Matrices/cont11.A.mtx",
        //                   "Matrices/dbic1.A.mtx",  "Matrices/ds-big.A.mtx", "Matrices/fome12.A.mtx",
        //                   "Matrices/fome13.A.mtx", "Matrices/gen4.A.mtx",   "Matrices/ken-18.A.mtx",
        //                   "Matrices/neos.A.mtx",
        //                   "Matrices/neos1.A.mtx",  "Matrices/neos2.A.mtx",  "Matrices/nug15.A.mtx",
        //                   "Matrices/rail02.A.mtx", "Matrices/self.A.mtx",   "Matrices/watson_2.A.mtx"};
        
        // char *filesB[] = {"Matrices/brand.B.mtx",  "Matrices/brandy.B.mtx", "Matrices/buildingenergy.B.mtx",
        //                   "Matrices/cont1.B.mtx",  "Matrices/cont4.B.mtx",  "Matrices/cont11.B.mtx",
        //                   "Matrices/dbic1.B.mtx",  "Matrices/ds-big.B.mtx", "Matrices/fome12.B.mtx",
        //                   "Matrices/fome13.B.mtx", "Matrices/gen4.B.mtx",   "Matrices/ken-18.B.mtx",
        //                   "Matrices/neos.B.mtx",
        //                   "Matrices/neos1.B.mtx",  "Matrices/neos2.B.mtx",  "Matrices/nug15.B.mtx",
        //                   "Matrices/rail02.B.mtx", "Matrices/self.B.mtx",   "Matrices/watson_2.B.mtx"};

        // char *filesC[] = {"brand.C.mtx",  "brandy.C.mtx", "buildingenergy.C.mtx",
        //                   "cont1.C.mtx",  "cont4.C.mtx",  "cont11.C.mtx",
        //                   "dbic1.C.mtx",  "ds-big.C.mtx", "fome12.C.mtx",
        //                   "fome13.C.mtx", "gen4.C.mtx",   "ken-18.C.mtx",
        //                   "neos.C.mtx",
        //                   "neos1.C.mtx",  "neos2.C.mtx",  "nug15.C.mtx",
        //                   "rail02.C.mtx", "self.C.mtx",   "watson_2.C.mtx"};


        // int numNames = sizeof(filesA) / sizeof(filesA[0]);
        // printf("%d \n", numNames);
        // for (int i = 0; i < numNames; i++){

        //     // MATRICE A
        //     CSC *A = create_sparse_matrix(filesA[i]);
        //     if (!A){
        //         printf("Failed to create A \n");
        //         return 1;
        //     }
        
        //     // MATRICE B
        //     CSC *B = create_sparse_matrix(filesB[i]);
        //     if (!B){
        //         printf("Failed to create B\n");
        //         destroy_matrix(A);
        //         return 1;
        //     }


        //     // Produit A x B
        //     CSC *C = matrix_matrix_product(A, B);
        //     if (!C){
        //         printf("Product A x B failed\n");
        //         destroy_matrix(A);
        //         destroy_matrix(B);
        //         continue;
        //         // return 1;
        //     }
        
        //     // Ecriture de C dans un fichier
        //     char *filename = filesC[i];
        //     unsigned short success = csc_to_file(C, filename);
        //     if (success){
        //         printf("A x B was successfully written in %s\n", filename);
        //     }

        //     destroy_matrix(A);
        //     destroy_matrix(B);
        //     destroy_matrix(C);
        // }
        // -------------------------------------------------- FIN TEST -----------------------------------------------//

        // MATRICE A
        CSC *A = create_sparse_matrix("watson_2.A.mtx");
        if (!A){
            printf("Failed to create A \n");
            return 1;
        }
       
        // // MATRICE B
        CSC *B = create_sparse_matrix("watson_2.B.mtx");
        if (!B){
            printf("Failed to create B\n");
            destroy_matrix(A);
            return 1;
        }


        // // Produit A x B
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

     else if (strcmp(argv[0], "./puissance") == 0){
         // MATRICE A
        CSC *A = create_sparse_matrix("self.B.mtx");
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
