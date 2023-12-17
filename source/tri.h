/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier tri.h
 */

#ifndef __TRI__
#define __TRI__


// ------------------------------------ QUICK SORT ----------------------------------- //

/**
 * swap
 * 
 * @brief Permute les valeurs de deux entiers
 *
 * @param a Pointeur vers le premier entier
 * @param b Pointeur vers le second entier
 */
void swap(int* a, int* b);

/**
 * partition
 * 
 * @brief Partitionne un tableau selon le dernier élément comme pivot
 *
 * @param arr Tableau d'entiers à partitionner
 * @param l Indice du début de la partition
 * @param h Indice de fin de la partition
 *
 * @return Indice du pivot après partitionnement
 */
int partition(int arr[], int l, int h);

/**
 * quickSortIterative
 * 
 * @brief Trie un tableau d'entiers de manière itérative en utilisant Quick Sort
 *
 * @param arr Tableau d'entiers à trier
 * @param l Indice du début du tableau
 * @param h Indice de fin du tableau
 * 
 * @return /
 */
void quickSortIterative(int arr[], int l, int h);


// ------------------------------------ MERGE SORT ----------------------------------- //

/**
 * mergeSort
 * 
 * @brief Trie les tableaux lignes[], cols[], et nnz[] en utilisant Merge Sort
 *
 * @param lignes Tableau d'entiers représentant les lignes
 * @param cols Tableau d'entiers représentant les colonnes
 * @param nnz Tableau de doubles représentant les valeurs non nulles
 * @param n Taille des tableaux
 * 
 * @return /
 */
void mergeSort(int lignes[], int cols[], double nnz[], int n);

/**
 * merge
 * 
 * @brief Fusionne deux parties du tableau trié lors du tri fusion
 *
 * @param lignes Tableau d'entiers représentant les lignes
 * @param cols Tableau d'entiers représentant les colonnes
 * @param nnz Tableau de doubles représentant les valeurs non nulles
 * @param l Indice du début de la première partie
 * @param m Indice du milieu
 * @param r Indice de fin de la deuxième partie
 * 
 * @return /
 */
void merge(int lignes[], int cols[], double nnz[], int l, int m, int r);

void swapDouble(double* a, double* b);

int partitionMatrix(int col[], int row[], double values[], int l, int h);

void quickSortIterativeMatrix(int row[], int col[], double values[], int l, int h);



#endif