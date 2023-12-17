/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier tri.c
 * 
 * SOURCE de l'algorithme : https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrice.h"
#include "tri.h"

static int min(int x, int y);

// ---------------------------------------------------------- QUICK SORT ------------------------------------------------------------------- //

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function is same in both iterative and recursive*/
int partition(int arr[], int l, int h)
{
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
void quickSortIterative(int arr[], int l, int h)
{
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

// ---------------------------------------------------------- MERGE SORT ------------------------------------------------------------------- //

// Utility function to find minimum of two integers
static int min(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int lignes[], int cols[], double nnz[], int n){
    assert(lignes != NULL && cols != NULL && nnz != NULL);
    int curr_size; // For current size of subarrays to be merged
                    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
                    // to be merged

    // Merge subarrays in bottom up manner. First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
    {
        // Pick starting point of different subarrays of current size
        for (left_start=0; left_start<n-1; left_start += 2*curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting 
            // point of right
            int mid = min(left_start + curr_size - 1, n-1);

            int right_end = min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(lignes, cols, nnz, left_start, mid, right_end);
        }
    }
}

/* Function to merge the two haves cols[l..m] and cols[m+1..r] of array cols[] */
void merge(int lignes[], int cols[], double nnz[], int l, int m, int r){
    assert(lignes != NULL && cols != NULL && nnz != NULL);
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
    int *colsL = malloc(n1 * sizeof(int));
    int *colsR = malloc(n2 * sizeof(int));
    int *lignesL = malloc(n1 * sizeof(int));
    int *lignesR = malloc(n2 * sizeof(int));
    double *nnzL = malloc(n1 * sizeof(double));
    double *nnzR = malloc(n2 * sizeof(double));

    // Stack for small arrays
	// int colsL[n1], colsR[n2];
    // int lignesL[n1], lignesR[n2];
    // double nnzL[n1], nnzR[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++){
		colsL[i] = cols[l + i];
        lignesL[i] = lignes[l + i];
        nnzL[i] = nnz[l + i];
    }

	for (j = 0; j < n2; j++){
		colsR[j] = cols[m + 1+ j];
        lignesR[j] = lignes[m + 1+ j];
        nnzR[j] = nnz[m + 1+ j];
    }

	/* Merge the temp arrays back into cols[l..r]*/
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2){
		if (colsL[i] <= colsR[j])
		{
			cols[k]   = colsL[i];
            lignes[k] = lignesL[i];
            nnz[k]    = nnzL[i];
			i++;
		}
		else
		{
			cols[k]   = colsR[j];
            lignes[k] = lignesR[j];
            nnz[k]    = nnzR[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1){
		cols[k] = colsL[i];
        lignes[k] = lignesL[i];
        nnz[k] = nnzL[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2){
		cols[k] = colsR[j];
        lignes[k] = lignesR[j];
        nnz[k] = nnzR[j];
		j++;
		k++;
	}

    free(colsL);
    free(colsR);
    free(lignesL);
    free(lignesR);
    free(nnzL);
    free(nnzR);
}
