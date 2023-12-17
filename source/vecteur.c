/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier vecteur.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "vecteur.h"

// ------------------------------------------------------------------------------------------- //

SparseVector *create_sparse_vector(double *vector, unsigned int n){
    assert(vector != NULL);

    unsigned int index = 0, nonZeros = 0;

    SparseVector *vect = malloc(sizeof(SparseVector));
    if (!vect){
        printf("Error creating a sparse vector : Allocation of sparse vector failed \n");
        return NULL;
    }

    vect->size = n;
    for (unsigned int i = 0; i < n; i++){
        if (vector[i] != 0 ){
            nonZeros += 1;
        }
    }
    
    vect->nnz = nonZeros;

    vect->i = malloc(nonZeros * sizeof(int));
    if (!vect->i){
        free(vect);
        printf("Error creating a sparse vector : Allocation of V.i failed\n");
        return NULL;
    }

    vect->x = malloc(nonZeros * sizeof(double));
    if (!vect->x){
        free(vect->i);
        free(vect);
        printf("Error creating a sparse vector : Allocation of V.x failed\n");
        return NULL;
    }
    
    for (unsigned int j = 0; j < n; j++){
        if(vector[j] != 0){
            vect->x[index] = vector[j];
            vect->i[index] = j;
            index++;
        }
    }
    
    return vect;
}

unsigned short vector_to_file(SparseVector *vect, char *filename){
    assert(vect != NULL && filename != NULL);

    FILE *fw = fopen(filename, "w");
    if (!fw){
        printf("Error : Failed to open %s\n", filename);
        return 0;
    }

    fprintf(fw, "%d %d\n", vect->size, vect->nnz);

    for (int i = 0; i < vect->nnz; i++ ){
        fprintf(fw, "%d %e\n", vect->i[i], vect->x[i]);
    }

    fclose(fw);

    return 1;
}

void destroy_vector(SparseVector *vect){
    assert(vect != NULL && vect->x != NULL && vect->i);

    free(vect->x);
    free(vect->i);
    free(vect);
}

double *generate_vector(int n){
    assert(n > 0);
    
    double *vect = malloc(n * sizeof(double));

    if (!vect){
        printf("Error : Failed to allocate generated vector\n");
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++){
        vect[i] = (double)rand() / RAND_MAX;
    }
       
    return vect;
}

void copy_vector(double *source, double *dest, int n){
    assert(source != NULL && dest != NULL && n > 0);

    for (int i = 0; i < n; i++){
        dest[i] = source[i];
    }
}

double *divide_vect_scalar(double *vect, int n, double scalaire){
    assert(vect != NULL && n > 0);

    for (int i = 0; i < n; i++){
        vect[i] /= scalaire;
    }

    return vect;
}

double get_largest_module(double *vect, int n){ 
    assert(vect != NULL && n > 0);

    double max = fabs(vect[0]); 

    for (int i = 1; i < n; i++){
        if (fabs(vect[i]) > fabs(max)){ 
            max = (vect[i]);
        }
    }

    return max;
}
