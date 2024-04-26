#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort_int(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                int k = A[j];
                A[j] = A[j - 1];
                A[j - 1] = k;
            }
        }
    }
}

void bubblesort_float(float A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                float k = A[j]; // Исправлено на тип float
                A[j] = A[j - 1];
                A[j - 1] = k;
            }
        }
    }
}

void insertsort_int(int A[], int n){
    int temp;

    for (int i = 1; i < n; i++)
    {   
        for (int j = i; j > 0 && A[j - 1] > A[j]; j--)
        {
            temp = A[j-1];
            A[j-1] = A[j];
            A[j] = temp; 
        }
    }
}

void insertsort_float(float A[], int n){
    float temp; // Исправлено на тип float

    for (int i = 1; i < n; i++)
    {   
        for (int j = i; j > 0 && A[j - 1] > A[j]; j--)
        {
            temp = A[j-1];
            A[j-1] = A[j];
            A[j] = temp; 
        }
    }
}

void rand_array_int(int A[], int n){
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }
}

void rand_array_float(float A[], int n){
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = (float)rand() / RAND_MAX;
    }
}
