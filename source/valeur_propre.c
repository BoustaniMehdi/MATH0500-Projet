#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "valeur_propre.h"
#include "produit.h"
#include "tri.h"


// Determine si 2 vecteurs sont egaux à une tolérance près
unsigned short vect_egaux(double *vect1, double *vect2, int n){
    assert(vect1 != NULL && vect2 != NULL && n > 0);

    for (int i = 0; i < n; i++) {
        if (fabs(vect1[i] - vect2[i]) > TOLERANCE) {
            return 0;  // Vecteur non-egaux
        }
    }
    return 1;
}

double *get_vect_propre(CSC *A, double *valPropre){
    assert(A != NULL && A->p != NULL && A->i != NULL && A->x != NULL && valPropre != NULL && A->nbCols == A->nbLignes);

    int iter = 1;

    int n = A->nbCols; // taille

    double *x = generer_vecteur(n); 
    
    if (!x){
        return NULL;
    }
    double *w = produit_matrice_vecteur(A, x, n); // w = Ax

    *valPropre = norme(w, n);

    // z = w/norm(w)
    double *z = diviser_vect_scalaire(w, n, *valPropre); // vect propre courant : normaliser le vecteur w

    while(iter < MAX_ITER){

        if(vect_egaux(x, z, n)){
            free(x);
            printf("iter = %d\n", iter);
            return w;
        }

        copier_vecteur(z, x, n); // x = z

        free(z);

        w = produit_matrice_vecteur(A, x, n);

        // w = produit_matrice_vecteur(A, z, n);
        *valPropre = norme(w, n);

        z = diviser_vect_scalaire(w, n, *valPropre);

        iter++;
    }

    free(x);

    return z;
}

