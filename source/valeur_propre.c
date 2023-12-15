#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "valeur_propre.h"
#include "produit.h"
#include "tri.h"



// ---------------------------------------------------- CHANGEMENTS -------------------------------------------------------------- //

double *get_vect_propre(CSC *A, double *valPropre){
    assert(A != NULL && A->nbCols == A->nbLignes);
    
    int n = A->nbCols; // taille
    double *x = generer_vecteur(n); // vecteur aléatoire géneré = z(0)
    
    if (!x){
        return NULL;
    }

    double *w = calloc(n, sizeof(double)); 
    if (!w){
        free(x);
        return NULL;
    }

    produit_matrice_vecteur(A, x, n, w); // w = Ax ( z(1) = A*z(0) )

    *valPropre = norme_infinie(w, n);

    double *z = diviser_vect_scalaire(w, n, *valPropre); // vect propre courant : normaliser le vecteur w
   
    int iter = 1;

    while(iter < MAX_ITER){
        if (vect_egaux(x, z, n)){ // vecteurs égaux à une tolérance près
            free(x);
            printf("iter = %d\n", iter);
            return w;
        }

        copy_vector(z, x, n); // x = z

        mult_mat_vect(A, x, n, w); // w = Ax

        *valPropre = norme_infinie(w, n); // valeur propre courante

        z = diviser_vect_scalaire(w, n, *valPropre); // normaliser le vecteur w

        iter++;     
    }

    free(x);

    return z;
}


// ------------------------------------------------------------------------------------------------------------------------------- //
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

