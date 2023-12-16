#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "valeur_propre.h"
#include "produit.h"
#include "tri.h"


// Determine si 2 vecteurs sont egaux à une tolérance près
unsigned short are_equal(double *vect1, double *vect2, int n){
    assert(vect1 != NULL && vect2 != NULL && n > 0);

    for (int i = 0; i < n; i++) {
        if (fabs(vect1[i] - vect2[i]) > TOLERANCE) {
            return 0;  // Vecteur non-egaux
        }
    }
    return 1;
}

double *get_eigen_vector(CSC *A, double *eigenValue){
    assert(A != NULL && A->p != NULL && A->i != NULL && A->x != NULL && eigenValue != NULL);

    int iter = 1;

    if (A->nbCols != A->nbRows){
        printf("Error : Matrix is not square\n");
        return NULL;
    }

    int n = A->nbCols; // taille

    double *x = generate_vector(n); // vecteur aléatoire géneré = z(0)
    
    if (!x){
        return NULL;
    }

    double *w = calloc(n, sizeof(double)); 

    if (!w){
        free(x);
        return NULL;
    }

    matrix_vector_product(A, x, n, w); // w = Ax ( z(1) = A*z(0) )

    *eigenValue = get_largest_module(w, n);

    double norme = fabs(*eigenValue);

    double *z = divide_vect_scalar(w, n, norme); // vect propre courant : normaliser le vecteur w

    while(iter < MAX_ITER){
        if (are_equal(x, z, n)){ // vecteurs égaux à une tolérance près
            free(x);
            printf("iter = %d\n", iter);
            return w;
        }

        copy_vector(z, x, n); // x = z

        matrix_vector_product(A, x, n, w); // w = Ax

        *eigenValue = get_largest_module(w, n); // valeur propre courante

        norme = fabs(*eigenValue);

        z = divide_vect_scalar(w, n, norme); // normaliser le vecteur w

        iter++;     
    }

    free(x);

    return z;
}

// ------------------------------------------------------------------------------------------------------------------------------- //
