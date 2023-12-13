#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>


#define DEBUT 1
#define MAX_ITER 10000
#define TOLERANCE 0.0001

typedef struct csc {
    int *p;
    int *i;
    double *x;
    int nz;
    int nbLignes;
    int nbCols;
}CSC;

typedef struct vect {
    int *i;
    double *x;
    int nz;
    int nbLignes;
}vectCreux;

typedef struct{
    int *ligne;
    int *colonne;
    double *valeur;
}MatriceInput;

void swap(int* a, int* b){
    assert(a != NULL && b != NULL);

    int t = *a;
    *a = *b;
    *b = t;
}

void swapDouble(double* a, double* b){
    assert(a != NULL && b != NULL);

    double t = *a;
    *a = *b;
    *b = t;
}
 
/* This function is same in both iterative and recursive*/
int partition(int arr[], int l, int h){
    assert(arr != NULL);

    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}
 
/* A[] --> Array to be sorted, 
   l  --> Starting index, 
   h  --> Ending index */
void quickSortIterative(int arr[], int l, int h){
    assert(arr != NULL);

    // Create an auxiliary stack
    int stack[h - l + 1];
 
    // initialize top of stack
    int top = -1;
 
    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;
 
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];
 
        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);
 
        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
 
        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

int partitionMatrice(int col[], int row[], double values[], int l, int h){
    assert(col != NULL);

    int x = col[h];
    int i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) {
        if (col[j] <= x) {
            i++;
            swap(&col[i], &col[j]);
            swap(&row[i], &row[j]);
            swapDouble(&values[i], &values[j]);
        }
    }
    swap(&col[i + 1], &col[h]);
    swap(&row[i + 1], &row[h]);
    swapDouble(&values[i + 1], &values[h]);
    return (i + 1);
}

void quickSortIterativeMatrice(int row[], int col[], double values[], int l, int h){
    assert(col != NULL);

    // Create an auxiliary stack
    int *stack = malloc((h-l+1)*sizeof(int));
 
    // initialize top of stack
    int top = -1;
 
    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;
 
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];
 
        // Set pivot element at its correct position
        // in sorted array
        int p = partitionMatrice(col,row, values, l, h);
 
        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
 
        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}

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

    if(fscanf(fptr, "%d %d %d", &matrice->nbLignes, &matrice->nbCols, &matrice->nz) != 3){
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
    matrice->i = malloc(matrice->nz * sizeof(int));
    if (!matrice->i){
        printf("Erreur creation de la matrice -- array i\n");
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    // Initialisation array x (non-nuls). Taille = # non-zeros
    matrice->x = malloc(matrice->nz * sizeof(double));
    if (!matrice->x){
        printf("Erreur creation de la matrice -- array x\n");
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    MatriceInput* entries = malloc(matrice->nz * sizeof(MatriceInput));

    if(!entries){
        printf("Erreur creation de stockage de la matrice\n");
        free(matrice->x);
        free(matrice->i);
        free(matrice->p);
        free(matrice);
        fclose(fptr);
        return NULL;
    }

    entries->ligne = malloc(matrice->nz * sizeof(int));
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

    entries->colonne = malloc(matrice->nz * sizeof(int));
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

    entries->valeur = malloc(matrice->nz * sizeof(double));
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

    while(indice < matrice->nz){
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
    

    quickSortIterativeMatrice(entries->ligne,entries->colonne, entries->valeur, 0, matrice->nz - 1);


    indice = 0;

    while(indice < matrice->nz){

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
double norme(double *vect, int n){ // norme 0 = nnz
    assert(vect != NULL);
    double max = fabs(vect[0]); // max en valeur absolue !!!!!!!!!!!
    for (int i = 1; i < n; i++){
        if (fabs(vect[i]) > max){
            max = fabs(vect[i]);
        }
    }
    return max;
}

// DIVISION VECTEUR PAR UN SCALAIRE
double *diviser_vect_scalaire(double *vect, int n, double scalaire){
    assert(vect != NULL);
    for (int i = 0; i < n; i++){
        vect[i] /= scalaire;
    }
    return vect;
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

unsigned short vect_egaux(double *vect1, double *vect2, int n){
    assert(vect1 != NULL && vect2 != NULL);
    int i = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(vect1[i] - vect2[i]) > TOLERANCE) {
            return 0;  // Vectors are not equal
        }
    }
    return 1;
}

void copy_vector(double *source, double *dest, int n){
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
        copy_vector(z, x, n); // x = z
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

// vectCreux *init_vecteur_creux(unsigned int *i, double *x, unsigned int nz, unsigned int nbLignes)

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



unsigned int get_nz(int *uni, int size, int *dest, int start){
    assert(uni != NULL && dest != NULL);
    if (size == 0 || size == 1){
        dest[start] = uni[0];
        return size;
    }
    dest[start] = uni[0];
    int nz = 1;
    for (int i = 1; i < size; i++){
        if (uni[i] != uni[i-1]){
            dest[start+nz] = uni[i];
            nz++;
        }
    }
    // printf("\n");
    return nz;
}

CSC *produit_matrice_matrice(CSC *A, CSC *B){
    assert(A != NULL && A->p != NULL && A->i != NULL && A->x != NULL && 
           B != NULL && B->p != NULL && B->i != NULL && B->x != NULL && 
           A->nbCols == B->nbLignes);
           

    CSC *C = malloc(sizeof(CSC));

    if (!C){
        printf("Erreur : Echec d'allocation de la matrice C\n");
        return NULL;
    }    
    C->p = malloc((B->nbCols +1) * sizeof(int));
    // C->i = malloc(B->nbCols * sizeof(int));
    if (!C->p){
        printf("Erreur : Echec d'allocation de C.p\n");
        free(C);
        return NULL;
    }

    C->nbLignes = A->nbLignes;
    C->nbCols = B->nbCols;
    C->p[0] = DEBUT;
    C->nz = 0;
    int m = A->nbLignes * B->nbCols;
    // int m = A->nz;
    unsigned int offset = 0; // pour y
    unsigned int count = 0;
    unsigned int nonZeros = 0;
    unsigned int indice = 0;
                 
    int *uni = malloc(A->nz * sizeof(int));

    if (!uni){
        printf("Erreur : Echec d'allocation pour l'union\n");
        free(C->p);
        free(C);
        return NULL;
    }

    double *y = calloc(m, sizeof(double)); // MAX TAILLE = ?

    if (!y){
        printf("Erreur : Echec d'allocation pour y (= resultat matrice vecteur)\n");
        free(C->p);
        free(C);
        return NULL;
    }

    int *tmpI = malloc(m * sizeof(int)); // MAX TAILLE = ?

    if (!tmpI){
        printf("Erreur : Echec d'allocation pour tmpI\n");
        free(C->p);
        free(C);
        return NULL;
    }
    for (int j = 0; j < B->nbCols; j++){ // parcourir les colonnes de B
        count = 0;

        for (int k = B->p[j] - DEBUT; k <= B->p[j+1] - 1 - DEBUT; k++){
            int currCol = B->i[k] - DEBUT;
            for (int i = A->p[currCol] - DEBUT; i <= A->p[currCol+1] - 1 - DEBUT; i++){
                uni[count] = A->i[i];
                y[A->i[i] - DEBUT + offset] += B->x[k] * A->x[i];
                count++;
            }
        }

        offset += B->nbLignes;

        if (count > 0){
            quickSortIterative(uni, 0, count-1); // trier l'union courante (avec doublons)
        }

        nonZeros = get_nz(uni, count, tmpI, C->nz);

        C->nz += nonZeros;
        
        C->p[j+1] = C->p[j] + nonZeros;
    }
   
    // REMPLIR C.x
    C->x = malloc(C->nz * sizeof(double));
    if(!C->x){
        printf("Erreur : Echec d'allocation de C.x \n");
        free(C->p);
        free(C);
        return NULL;
    }
    int idx = 0;
    for (int i = 0; i < m; i++){
        if (y[i] != 0){
            C->x[idx] = y[i];
            idx++;
        }
    }
    // REMPLIR C.i
    C->i = malloc(C->nz * sizeof(int));
    if(!C->i){
        printf("Erreur : Echec d'allocation de C.i \n");
        free(C->p);
        free(C->x);
        free(C);
        return NULL;
    }
    for (int j = 0; j < C->nz; j++){
        C->i[j] = tmpI[j];
    }
    free(uni);
    free(tmpI);
    free(y);
    return C;
}

void detruire_matrice(CSC *mat){
    assert(mat != NULL);
    free(mat->i);
    free(mat->x);
    free(mat->p);
    free(mat);
}

int main(){

//    CSC *matCreuse = creer_matrice("Matrices/gen4.B.mtx");

//    printf("Nombre de lignes : %d\n", matCreuse->nbLignes);
//    printf("Nombre de colonnes : %d\n", matCreuse->nbCols);
//    printf("Nombre de non-nuls : %d\n", matCreuse->nz);

// --------------------------- A --------------------------------- //
// METTRE LE NOM DU FICHIER A ICI
CSC *A = creer_matrice("brand.A.mtx");
// CSC *A = creer_matrice("Matrices/neos.A.mtx");
   //printf("Nombre de lignes de A = %d \n", A->nbLignes);
   //printf("Nombre de colonnes de A = %d \n", A->nbCols);
   //printf("Nombre de non-zeros de A = %d \n", A->nz);

//    printf("liste des non-nuls A.x : ");
//    for (int i = 0; i < A->nz; i++){
//     printf(" %f", A->x[i]);
//    }
//    printf("\n");

//    printf("liste des lignes A.i : ");
//    for (int j = 0; j < A->nz; j++){
//     printf(" %d", A->i[j]);
//    }
//    printf("\n");

//    printf("liste des cols A.p : ");
//    for (int j = 0; j < A->nbCols + 1; j++){
//     printf(" %d", A->p[j]);
//    }
//    printf("\n");

// --------------------------- B --------------------------------- //
// METTRE LE NOM DU FICHIER B ICI
CSC *B = creer_matrice("brand.B.mtx");
// CSC *B = creer_matrice("Matrices/neos.B.mtx");
   //printf("Nombre de lignes de B = %d \n", B->nbLignes);
   //printf("Nombre de colonnes de B = %d \n", B->nbCols);
   //printf("Nombre de non-zeros de B = %d \n", B->nz);
   //printf("\n");
//    printf("liste des non-nuls B.x : ");
//    for (int i = 0; i < B->nz; i++){
//     printf(" %d %f",B->i[i], B->x[i]);
//    }
//    printf("\n");

//    printf("liste des lignes B.i : ");
//    for (int j = 0; j < B->nz; j++){
//     printf(" %d", B->i[j]);
//    }
//    printf("\n");

//    printf("liste des cols B.p : ");
//    for (int j = 0; j < B->nbCols + 1; j++){
//     printf(" %d", B->p[j]);
//    }
//    printf("\n");
//    printf("\n");

// --------------------------- C --------------------------------- //

   CSC *C = produit_matrice_matrice(A, B);
   printf("Nombre de lignes de C = %d \n", C->nbLignes);
   printf("Nombre de colonnes de C = %d \n", C->nbCols);
   printf("Nombre de non-zeros de C = %d \n", C->nz);

    printf("\n");
    printf("liste des non-nuls C.x : ");
    for (int i = 0; i < C->nz; i++){
     printf(" %f", C->x[i]);
    }
    printf("\n");

    printf("liste des lignes C.i : ");
    for (int j = 0; j < C->nz; j++){
     printf(" %d", C->i[j]);
    }
    printf("\n");

    printf("liste des cols C.p : ");
    for (int j = 0; j < C->nbCols + 1; j++){
     printf(" %d", C->p[j]);
    }
    printf("\n");
    printf("\n");


  detruire_matrice(A);
  //detruire_matrice(B);
  //detruire_matrice(C);


   return 0;
}


