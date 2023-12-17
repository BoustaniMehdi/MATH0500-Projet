/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier matrice.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "matrice.h"
#include "tri.h"

/**
 * get_entries_input
 * 
 * @brief Crée une matrice en lisant le fichier mtx.
 *
 * @param filename le nom du fichier mtx contenant la matrice creuse
 * 
 * @pre filename != NULL
 *
 * @return MatrixInput *, un pointeur vers notre matrice.
 *         NULL en cas d'erreur.
 */
static MatrixInput *get_entries_input(char *filename);

/**
 * destroy_entries
 * 
 * @brief Détruit (free) notre matrice input.
 *
 * @param entries la matrice input à détruire
 * 
 * @pre entries != NULL, entries->rows != NULL, entries->cols != NULL, entries->values != NULL
 *
 * @return /
 */
static void destroy_entries(MatrixInput *entries);

static MatrixInput *get_entries_input(char *filename){
    assert(filename != NULL);

    int row = 0, col = 0, index = 0, indexEntries = 0;
    double value = 0;

    FILE *fptr = fopen(filename, "r");
    if (!fptr){
        printf("Error : Failed to open %s\n", filename);
        return NULL;
    }

    MatrixInput *entries = malloc(sizeof(MatrixInput));
    if (!entries){
        printf("Error : Failed to allocate entries\n");
        fclose(fptr);
        return NULL;
    }

    if (fscanf(fptr, "%d %d %d", &entries->nbRows, &entries->nbCols, &entries->nnz) != 3){
        printf("Error : Failed to read file -- Corrupted file\n");
        fclose(fptr);
        free(entries);
        return NULL;
    }
    
    entries->rows = malloc(entries->nnz * sizeof(int));
    if (!entries->rows){
        printf("Error : Failed to allocate entries.rows\n ");
        fclose(fptr);
        free(entries);
        return NULL;
    }

    entries->cols = malloc(entries->nnz * sizeof(int));
    if (!entries->cols){
        printf("Error : Failed to allocate entries.cols\n ");
        fclose(fptr);
        free(entries->rows);
        free(entries);
        return NULL;
    }

    entries->values = malloc(entries->nnz * sizeof(double));
    if (!entries->values){
        printf("Error : Failed to allocate entries.values\n ");
        fclose(fptr);
        free(entries->rows);
        free(entries->cols);
        free(entries);
        return NULL;
    }

    while (index < entries->nnz){
        if(fscanf(fptr, "%d %d %lf", &row, &col, &value) != 3){
            printf("Error reading file : Incomplete or corrupted file\n");
            fclose(fptr);
            free(entries->values);
            free(entries->rows);
            free(entries->cols);
            free(entries);
            return NULL;
        }

        // Ne pas prendre en compte les zeros dans le fichier
        if (value != 0){
            entries->rows[indexEntries] = row;
            entries->cols[indexEntries] = col;
            entries->values[indexEntries] = value;
            indexEntries++;
        }

        index ++;
    }
    entries->nnz = indexEntries;

    fclose(fptr);

    return entries;
}

CSC *create_sparse_matrix(char *inputfile){
    assert(inputfile != NULL);

    int currCol = 0, indexCol = 0, index = 0;

    // Chercher les données du fichier
    MatrixInput *entries = get_entries_input(inputfile);
    if (!entries){
        printf("Failed to fetch data from %s\n", inputfile);
        return NULL;
    }

    CSC *matrix = malloc(sizeof(CSC));
    if (!matrix){
        printf("Error : Failed to allocate a CSC \n");
        destroy_entries(entries);
        return NULL;
    }

    matrix->nbCols = entries->nbCols;
    matrix->nbRows = entries->nbRows;
    matrix->nnz = entries->nnz;

    matrix->p = malloc((matrix->nbCols+1) * sizeof(int));
    if (!matrix->p){
        printf("Error : Failed to allocate p array\n");
        destroy_entries(entries);
        free(matrix);
        return NULL;
    }

    matrix->i = malloc(matrix->nnz * sizeof(int));
    if(!matrix->i){
        printf("Error : Failed to allocate i array\n");
        destroy_entries(entries);
        free(matrix->p);
        free(matrix);
        return NULL;
    }

    matrix->x = malloc(matrix->nnz * sizeof(double));
    if (!matrix->x){
        printf("Error : Failed to allocate x array\n");
        destroy_entries(entries);
        free(matrix->p);
        free(matrix->i);
        free(matrix);
        return NULL;
    }

    // Trier les données en fonction des colonnes    
    mergeSort(entries->rows, entries->cols, entries->values, matrix->nnz);

    // Remplissage des données dans la matrice CSC
    while(index < matrix->nnz){

        matrix->x[index] = entries->values[index];
        matrix->i[index] = entries->rows[index];

        if(entries->cols[index] != currCol){

            if(entries->cols[index] - currCol > 1){
                for (int j = 0; j < entries->cols[index]-currCol - 1; j++){

                    matrix->p[indexCol++] = index + 1;
                }
            }

            matrix->p[indexCol++] = index + 1;

            currCol = entries->cols[index];
        }

        index ++;
    }

    matrix->p[indexCol] = index + 1;

    for (int i = indexCol+1; i < matrix->nbCols + 1; i++){
      matrix->p[i] = matrix->p[indexCol];
    }
    
    destroy_entries(entries);
   
    return matrix;
}

unsigned short csc_to_file(CSC *matrix, char *filename){
    assert(matrix != NULL && matrix->p != NULL && matrix->i != NULL && matrix->x != NULL && filename != NULL);

    int nz = 0;

    FILE *fw = fopen(filename, "w");

    if (!fw){
        printf("Error : Failed to open %s\n", filename);
        return 0;
    }
    
    fprintf(fw, "%d %d %d\n", matrix->nbRows, matrix->nbCols, matrix->nnz);
   
    for (int i = 0; i <= matrix->nbCols-1 && nz < matrix->nnz ;i++){
        for(int j = matrix->p[i]; j <= matrix->p[i+1] - 1; j++){

            if (fabs(matrix->x[j-START]) < TOLNUMBER){
                fprintf(fw, "%d %d %e\n", matrix->i[j-START], i+START, matrix->x[j-START]);// Ecrire sous format %e si on est < TOLNUMBER
            }
            else {
                fprintf(fw, "%d %d %lf\n", matrix->i[j-START], i+START, matrix->x[j-START]);
            }
            
            nz++;
        }
    }

    fclose(fw);

    return 1;
}

void destroy_matrix(CSC *matrix){
    assert(matrix != NULL && matrix->i != NULL && matrix->x != NULL && matrix->p != NULL);

    free(matrix->i);
    free(matrix->x);
    free(matrix->p);
    free(matrix);
}

static void destroy_entries(MatrixInput *entries){
    assert(entries != NULL && entries->rows != NULL && 
      entries->cols != NULL && entries->values != NULL);
    
    free(entries->rows);
    free(entries->cols);
    free(entries->values);
    free(entries);
}
