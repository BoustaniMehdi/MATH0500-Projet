/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier tri.h
 */

#ifndef __TRI__
#define __TRI__


// quicksort pour un seul tableau
void swap(int* a, int* b);
int partition(int arr[], int l, int h);
void quickSortIterative(int arr[], int l, int h);

// ------------------------------------ MERGE SORT ----------------------------------- //
void mergeSort(int lignes[], int cols[], double nnz[], int n);
void merge(int lignes[], int cols[], double nnz[], int l, int m, int r);


#endif