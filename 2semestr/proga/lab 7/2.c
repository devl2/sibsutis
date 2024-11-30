#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calculate_row_sums(int **arr, int rows) {
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 1; j <= arr[i][0]; j++) {
            sum += arr[i][j];
        }
        printf("Сумма элементов строки %d: %d\n", i + 1, sum);
    }
}

int main() {
    srand(time(NULL)); 

    int str = 10; 
    int **arr = (int **)malloc(str * sizeof(int *));


    printf("Двумерный массив:\n");
    for (int i = 0; i < str; i++) {
        int dlina = rand() % 9 + 2; 
        arr[i] = (int *)malloc((dlina + 1) * sizeof(int));
        arr[i][0] = dlina; 

        printf("Строка %d (%d элементов): ", i + 1, dlina);
        for (int j = 1; j <= dlina; j++) {
            arr[i][j] = rand() % 10 + 1; 
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    calculate_row_sums(arr, str); 

    for (int i = 0; i < str; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
