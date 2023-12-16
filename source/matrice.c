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

MatrixInput *create_input_matrix(CSC *matrix, FILE *fptr){
    assert(matrix != NULL && matrix->p != NULL && matrix->i != NULL && matrix->x != NULL && fptr != NULL);

    int row = 0, col = 0, index = 0; 
    double value = 0;

    MatrixInput* entries = malloc(sizeof(MatrixInput));

    if(!entries){
        printf("Error : Failed to store the entries of the matrix\n");
        free(matrix->x);
        free(matrix->i);
        free(matrix->p);
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    entries->rows = malloc(matrix->nnz * sizeof(int));
    if(!entries->rows){
        printf("Error : Failed to store rows of the matrix\n");
        free(entries);
        free(matrix->x);
        free(matrix->i);
        free(matrix->p);
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    entries->cols = malloc(matrix->nnz * sizeof(int));
    if(!entries->cols){
        printf("Error : Failed to store columns of the matrix \n");
        free(entries->rows);
        free(entries);
        free(matrix->x);
        free(matrix->i);
        free(matrix->p);
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    entries->values = malloc(matrix->nnz * sizeof(double));
    if(!entries->values){
        printf("Error : Failed to store non-zeros of the matrix \n");
        free(entries->cols);
        free(entries->rows);
        free(entries);
        free(matrix->x);
        free(matrix->i);
        free(matrix->p);
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    while(index < matrix->nnz){
        if(fscanf(fptr, "%d %d %lf", &row, &col, &value) != 3){
            printf("Error reading file : Corrupted file\n");
            free(entries->values);
            free(entries->cols);
            free(entries->rows);
            free(entries);
            free(matrix->x);
            free(matrix->i);
            free(matrix->p);
            free(matrix);
            fclose(fptr);
            return NULL;
        }

        entries->rows[index] = row;
        entries->cols[index] = col;
        entries->values[index] = value;

        index++;

    }

    return entries;

}

CSC *create_sparse_matrix(char *inputfile){
    assert(inputfile != NULL);

    int currCol = 0, indexCol = 0, index = 0;
    
    CSC *matrix = malloc(sizeof(CSC));
    if (!matrix){
        printf("Error : Failed to allocate a CSC \n");
        return NULL;
    }

    FILE *fptr = fopen(inputfile, "r");
    if(!fptr){
        printf("Error : Failed to open %s\n", inputfile);
        free(matrix);
        return NULL;
    }

    if(fscanf(fptr, "%d %d %d", &matrix->nbRows, &matrix->nbCols, &matrix->nnz) != 3){
        printf("Error : Failed to read file : Corrupted file\n");
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array p (colonnes). Taille = # colonnes + 1
    matrix->p = malloc((matrix->nbCols+1) * sizeof(int));
    if (!matrix->p){
        printf("Error : Failed to allocate p array\n");
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array i (lignes). Taille = # non-zeros
    matrix->i = malloc(matrix->nnz * sizeof(int));
    if (!matrix->i){
        printf("Error : Failed to allocate i array\n");
        free(matrix->p);
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array x (non-nuls). Taille = # non-zeros
    matrix->x = malloc(matrix->nnz * sizeof(double));
    if (!matrix->x){
        printf("Error : Failed to allocate x array\n");
        free(matrix->i);
        free(matrix->p);
        free(matrix);
        fclose(fptr);
        return NULL;
    }

    MatrixInput* entries = create_input_matrix(matrix, fptr);

    mergeSort(entries->rows, entries->cols, entries->values, matrix->nnz);
    // quickSortIterativematrix(entries->rows,entries->cols, entries->values, 0, matrix->nnz - 1);

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

    fclose(fptr);   

    free(entries->rows);
    free(entries->cols);
    free(entries->values);
    free(entries);

    return matrix;
}

unsigned short csc_to_file(CSC *matrix, char *filename){
    assert(matrix != NULL && matrix->p != NULL && matrix->i != NULL && matrix->i != NULL && filename != NULL);

    int nz = 0;

    FILE *fw = fopen(filename, "w");
    if (!fw){
        printf("Error : Failed to open %s\n", filename);
        return 0;
    }

    fprintf(fw, "%d %d %d\n", matrix->nbRows, matrix->nbCols, matrix->nnz);
    
    for (int i = 0; i <= matrix->nbCols-1 && nz < matrix->nnz ;i++){
        for(int j = matrix->p[i]; j <= matrix->p[i+1] - 1; j++){
            fprintf(fw, "%d %d %lf\n", matrix->i[j-START], i+START, matrix->x[j-START]);           
            nz++; 
        }
    }

    fclose(fw);

    return 1;
}

void destroy_matrix(CSC *matrix){
    assert(matrix != NULL && matrix->p != NULL && matrix->i != NULL && matrix->x != NULL);

    free(matrix->p);
    free(matrix->i);
    free(matrix->x);
    free(matrix);
}