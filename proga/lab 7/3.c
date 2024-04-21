#include <stdio.h>
#include <stdlib.h>

void sortDec(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int lin_perebor(int arr[], int n, int target, int *sr) {
    *sr = 0;
    for (int i = 0; i < n; i++) {
        (*sr)++;
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}


int binary(int arr[], int size, int target, int *sr) {
    int left = 0, right = size - 1;
    *sr = 0;
    while (left <= right) {
        (*sr)++;
        int mid = (left + right) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1; 
}

int main() {
    int N1 = 100;
    int N2 = 1000;
    int arr1[N1], arr2[N2];
    int index, sr;
   
    for (int i = 0; i < N1; i++) {
        arr1[i] = rand() % 1000;
    }

    for (int i = 0; i < N2; i++) {
        arr2[i] = rand() % 1000;
    }

    sortDec(arr1, N1);
    sortDec(arr2, N2);

    int target1 = arr1[75];
    int target2 = arr2[250];

    index = lin_perebor(arr1, N1, target1, &sr);
    printf("линейный поиск во 1-м:\n");
    printf("цель: %d, сравнения: %d\n", index, sr);
    printf("\n");

    index = binary(arr1, N1, target1, &sr);
    printf("бинарный поиск во 1-м:\n");
    printf("цель: %d, сравнения: %d\n", index, sr);
    printf("\n");

    index = lin_perebor(arr2, N2, target2, &sr);
    printf("линейный поиск во 2-м:\n");
    printf("цель: %d, сравнения: %d\n", index, sr);
    printf("\n");

    index = binary(arr2, N2, target2, &sr);
    printf("бинарный поиск во 2-м:\n");
    printf("цель: %d, сравнения: %d\n", index, sr);
    printf("\n");

    return 0;
}
