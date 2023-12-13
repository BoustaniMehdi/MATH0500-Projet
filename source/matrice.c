/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier matrice.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "matrice.h"
#include "tri.h"


// ---------------------------------------------------- ABDEL ------------------------------------------------------- //
unsigned short CSC_vers_fichier(CSC *matCreuse, char *filename){
    assert(matCreuse != NULL && filename != NULL);
    FILE *fw = fopen(filename, "w");
    if (!fw){
        printf("Erreur ouverture du fichier : %s\n", filename);
        return 0;
    }
    fprintf(fw, "%d %d %d\n", matCreuse->nbLignes, matCreuse->nbCols, matCreuse->nnz);
    for (int i = 0; i <= matCreuse->nbCols-1; i++){
        for(int j = matCreuse->p[i]; j <= matCreuse->p[i+1] - 1; j++){
            fprintf(fw, "%d %d %lf\n", matCreuse->i[j-DEBUT], i+DEBUT, matCreuse->x[j-DEBUT]);
        }
    }
    fclose(fw);
    return 1;
}

void detruire_matrice(CSC *mat){
    assert(mat != NULL);
    free(mat->i);
    free(mat->x);
    free(mat->p);
    free(mat);
}

// -------------------------------------------------------------------------------------------------------------------- //

CSC *creer_matrice(char *fichierInput){
    assert(fichierInput != NULL);

    int ligne = 0, col = 0, colCourant = 0, indiceCol = 0, indice = 0;
    double valeur = 0;
    
    CSC *matrice = malloc(sizeof(CSC));
    if (!matrice){
        printf("Erreur creation de la matrice\n");
        return NULL;
    }

    FILE *fptr = fopen(fichierInput, "r");
    if(!fptr){
        printf("Erreur ouverture du fichier input\n");
        free(matrice);
        return NULL;
    }

    if(fscanf(fptr, "%d %d %d", &matrice->nbLignes, &matrice->nbCols, &matrice->nnz) != 3){
        printf("Erreur lecture : fichier corrompu\n");
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array p (colonnes). Taille = # colonnes + 1
    matrice->p = malloc((matrice->nbCols+1) * sizeof(int));
    if (!matrice->p){
        printf("Erreur creation de la matrice -- array p\n");
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array i (lignes). Taille = # non-zeros
    matrice->i = malloc(matrice->nnz * sizeof(int));
    if (!matrice->i){
        printf("Erreur creation de la matrice -- array i\n");
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array x (non-nuls). Taille = # non-zeros
    matrice->x = malloc(matrice->nnz * sizeof(double));
    if (!matrice->x){
        printf("Erreur creation de la matrice -- array x\n");
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    MatriceInput* entries = malloc(matrice->nnz * sizeof(MatriceInput));

    if(!entries){
        printf("Erreur creation de stockage de la matrice\n");
        free(matrice->x);
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    entries->ligne = malloc(matrice->nnz * sizeof(int));
    if(!entries->ligne){
        printf("Erreur creation de stockage du tableau ligne\n");
        free(entries);
        free(matrice->x);
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    entries->colonne = malloc(matrice->nnz * sizeof(int));
    if(!entries->colonne){
        printf("Erreur creation de stockage du tableau colonne\n");
        free(entries->ligne);
        free(entries);
        free(matrice->x);
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    entries->valeur = malloc(matrice->nnz * sizeof(double));
    if(!entries->valeur){
        printf("Erreur creation de stockage du tableau valeur\n");
        free(entries->colonne);
        free(entries->ligne);
        free(entries);
        free(matrice->x);
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    while(indice < matrice->nnz){
        if(fscanf(fptr, "%d %d %lf", &ligne, &col, &valeur) != 3){
            printf("Erreur lecture : fichier corrompu\n");
            return NULL;
        }

        entries->ligne[indice] = ligne;
        entries->colonne[indice] = col;
        entries->valeur[indice] = valeur;

        indice++;

    }

    //for (int i = 0; i < 15; i++)
    //{
        //printf("%d %d %lf\n", entries->ligne[i], entries->colonne[i], entries->valeur[i]);
    //}
    
    //printf("\n");
    

    quickSortIterativeMatrice(entries->ligne,entries->colonne, entries->valeur, 0, matrice->nnz - 1);


    indice = 0;

    while(indice < matrice->nnz){

        matrice->x[indice] = entries->valeur[indice];
        matrice->i[indice] = entries->ligne[indice];

        if(entries->colonne[indice] != colCourant){

            if(entries->colonne[indice] - colCourant > 1){
                for (int j = 0; j < entries->colonne[indice]-colCourant - 1; j++){
                    
                    matrice->p[indiceCol++] = indice + 1;
                }
            }
            
            matrice->p[indiceCol++] = indice + 1;
            
            colCourant = entries->colonne[indice];
        }

        indice ++;
    }

    matrice->p[indiceCol] = indice + 1;

    fclose(fptr);   

    free(entries->ligne);
    free(entries->colonne);
    free(entries->valeur);
    free(entries);

    return matrice;
}

