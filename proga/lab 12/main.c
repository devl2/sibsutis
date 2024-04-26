#include <stdio.h>
#include <time.h>
#include "sort.h"


double int_timer(void (*sort_func1)(int[], int), int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    sort_func1(arr, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

double float_timer(void (*sort_func2)(float[], int), float arr[], int n) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    sort_func2(arr, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}


int main() {
    const int n = 10000;

    int int_array[n];
    float float_array[n];

    rand_array_int(int_array, n);
    rand_array_float(float_array, n);

    double time_bubble_int = int_timer(bubblesort_int, int_array, n);
    double time_bubble_float = float_timer(bubblesort_float, float_array, n);

    double time_insertion_int = int_timer(insertsort_int, int_array, n);
    double time_insertion_float = float_timer(insertsort_float, float_array, n);

    printf("Bubble Sort (int): %f seconds\n", time_bubble_int);
    printf("Bubble Sort (float): %f seconds\n", time_bubble_float);

    printf("Insertion Sort (int): %f seconds\n", time_insertion_int);
    printf("Insertion Sort (float): %f seconds\n", time_insertion_float);

    return 0;
}
