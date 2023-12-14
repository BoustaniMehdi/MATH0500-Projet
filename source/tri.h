/*
 * Auteur : Boustani Mehdi, Alabashityalshaier Abdelkader -- Université de Liège
 * Projet de programmation MATH0500
 * Fichier tri.h
 */

#ifndef __TRI__
#define __TRI__

void swap(int* a, int* b);

int partition(int arr[], int l, int h);

void quickSortIterative(int arr[], int l, int h);

void swapDouble(double* a, double* b);

int partitionMatrice(int col[], int row[], double values[], int l, int h);

void quickSortIterativeMatrice(int row[], int col[], double values[], int l, int h);

#endif