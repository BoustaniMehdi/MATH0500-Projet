/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier main.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrice.h"
#include "produit.h"
#include "vecteur.h"
#include "valeur_propre.h"

int main(int argc, char *argv[]){

    if (argc < 1) {
        printf("Problème lors de l'exécution du programme\n");
        return 1;
    }

    if(strcmp(argv[0], "./produit") == 0){
        CSC *A = creer_matrice("matrices/cont11.A.mtx");
        CSC *B = creer_matrice("matrices/cont11.B.mtx");

        CSC *C = produit_matrice_matrice(A, B);

        CSC_vers_fichier(C, "produit.mtx");
    }

    else if (strcmp(argv[0], "./puissance") == 0){
        printf("puissance\n");
    }

    else{
        printf("Problème lors de l'exécution du programme\n");
    }

    return 0;
}