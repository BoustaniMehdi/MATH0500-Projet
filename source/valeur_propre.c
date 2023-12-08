#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "valeur_propre.h"

double *mult_mat_vect(CSC *matCreuse, double *vect, int n){
    assert(matCreuse != NULL && vect != NULL);
    if (matCreuse->nbLignes != n){
        printf("La multiplication n'est pas définie entre la matrice et le vectuer\n");
        return NULL;
    }
    // le vecteur produit
    double *y = calloc(n, sizeof(double));
    if (!y){
        printf("Echec du produit MATRICE x VECTEUR : Allocation du vecteur produit échouée\n");
        return NULL;
    }

    // ----------------------------------Indexing starting at 1 ------------------------------------- //
    for (int i = 0; i < n; i++){
        for (int j = matCreuse->p[i]-1; j < matCreuse->p[i+1]-1; j++){
            y[matCreuse->i[j]-1] += vect[i] * matCreuse->x[j]; 

        }
    }
    return y;
}

// RENVOIE LA NORME INFINIE D'UN VECTEUR (max component)
double norme(double *vect, int n){ 
    assert(vect != NULL);
    double max = fabs(vect[0]); // max en valeur absolue !!!!!!!!!!!
    for (int i = 1; i < n; i++){
        if (fabs(vect[i]) > max){
            max = fabs(vect[i]);
        }
    }
    return max;
}

// Generer un vecteur aleatoire
double *generer_vecteur(int n){
    double *vect = malloc(n * sizeof(double));
    if (!vect){
        printf("Erreur : Echec allocation -- Echec generation du vecteur\n");
        return NULL;
    }
    for (int i = 0; i < n; i++){
        // if (i == 0)
            vect[i] = 1; // full 1 ou creux?
        // else 
        //     vect[i] = 0;
    }
       
    return vect;
}

// Determine si 2 vecteurs sont egaux à une tolérance près
unsigned short vect_egaux(double *vect1, double *vect2, int n){
    assert(vect1 != NULL && vect2 != NULL);
    int i = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(vect1[i] - vect2[i]) > TOLERANCE) {
            return 0;  // Vecteur non-egaux
        }
    }
    return 1;
}

void copier_vecteur(double *source, double *dest, int n){
    assert(source != NULL && dest != NULL);
    for (int i = 0; i < n; i++){
        dest[i] = source[i];
    }
}

double *get_vect_propre(CSC *A, double *valPropre){
    assert(A != NULL);
    if (A->nbCols != A->nbLignes){
        printf("La matrice n'est pas carrée et nous ne pouvons pas trouver une valeur propre\n");
        return NULL;
    }
    int n = A->nbCols; // taille
    double *x = generer_vecteur(n); 
    
    if (!x){
        return NULL;
    }
    double *w = mult_mat_vect(A, x, n); // w = Ax
    *valPropre = norme(w, n);

    // z = w/norm(w)
    double *z = diviser_vect_scalaire(w, n, *valPropre); // vect propre courant : normaliser le vecteur w
   
    int iter = 1;
    while(iter < MAX_ITER){
        if (vect_egaux(x, z, n)){
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

vectCreux *creer_vecteur_creux(double *vectTableau){
    assert(vectTableau != NULL);
    vectCreux *vect = malloc(sizeof(vectCreux));
    if (!vect){
        printf("Erreur : Echec creation du vecteur creux\n");
        return NULL;
    }
    unsigned int nonZeros = 0;
    size_t n = sizeof(vectTableau);
    vect->nbLignes = n;
    for (int i = 0; i < n; i++){
        if (vectTableau[i] != 0){
            nonZeros += 1;
        }
    }
    vect->nz = nonZeros;
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
    unsigned int indice = 0;
    for (int j = 0; j < n; j++){
        if(vectTableau[j] != 0){
            vect->x[indice] = vectTableau[j];
            vect->i[indice] = j;
        }
    }
    return vect;
}
