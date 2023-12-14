#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "valeur_propre.h"

// RENVOIE LA NORME INFINIE D'UN VECTEUR (max component)
double norme(double *vect, int n){ 
    assert(vect != NULL && n > 0);

    double max = fabs(vect[0]); // max en valeur absolue !!!!!!!!!!!

    for (int i = 1; i < n; i++){
        if (fabs(vect[i]) > max){
            max = fabs(vect[i]);
        }
    }

    return max;
}

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
    double *w = matrice_vecteur(A, x, n); // w = Ax

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

        w = mult_mat_vect(A, x, n);

        // w = mult_mat_vect(A, z, n);
        *valPropre = norme(w, n);

        z = diviser_vect_scalaire(w, n, *valPropre);

        iter++;
    }

    free(x);

    return z;
}

vectCreux *creer_vecteur_creux(double *vectTableau, unsigned int n){
    assert(vectTableau != NULL && n > 0);

    unsigned int nonZeros = 0, indice = 0;

    vectCreux *vect = malloc(sizeof(vectCreux));

    if (!vect){
        printf("Erreur : Echec creation du vecteur creux\n");
        return NULL;
    }
    
    vect->taille = n;
    
    for (int i = 0; i < n; i++){
        if (vectTableau[i] != 0){
            nonZeros += 1;
        }
    }

    vect->nnz = nonZeros;
    vect->i = malloc(nonZeros * sizeof(int));

    if (!vect->i){
        free(vect);
        printf("Erreur : Echec allocation vecteur creux\n");
        return NULL;
    }

    vect->x = malloc(nonZeros * sizeof(double));
    if (!vect->x){
        free(vect->i);
        free(vect);
        printf("Erreur : Echec allocation vecteur creux\n");
        return NULL;
    }

    for (int j = 0; j < n; j++){
        if(vectTableau[j] != 0){
            vect->x[indice] = vectTableau[j];
            vect->i[indice] = j;
        }
    }

    return vect;
}
