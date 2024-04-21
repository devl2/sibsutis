#include <stdio.h>
#include <time.h>

void zero_elements_between_min(int arr[], int n) {
    
    int minIndex1 = 0, minIndex2 = 0;
    if (arr[minIndex1] > arr[minIndex2]) {
        int temp = minIndex1;
        minIndex1 = minIndex2;
        minIndex2 = temp;
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] < arr[minIndex1]) {
            minIndex2 = minIndex1;
            minIndex1 = i;
        } else if (arr[i] < arr[minIndex2]) {
            minIndex2 = i;
        }
    }
    
    int start, end;
        if (minIndex1 < minIndex2)
        {
            start = minIndex1;
            end = minIndex2;
        } else {
            start = minIndex2;
            end = minIndex1;
        }

    for (int i = start + 1; i < end; i++) {
        arr[i] = 0;
    }
}

int main() {
    int n = 10;
    int arr[n];
    
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10 + 1;
    }

    printf("Массив до обработки:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    zero_elements_between_min(arr, n); 
    
    printf("Массив после обработки:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
