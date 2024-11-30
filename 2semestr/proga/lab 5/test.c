#include <stdio.h>
#include <stdlib.h>

void generate_matrix(int *A, int m, int k) {
    int rows = m / k + (m % k != 0);  // количество строк
    int **B = (int **)malloc(rows * sizeof(int *));  // выделяем память под матрицу B
    int i, j;

    // инициализируем матрицу B нулями
    for (i = 0; i < rows; i++) {
        B[i] = (int *)malloc(k * sizeof(int));
        for (j = 0; j < k; j++) {
            B[i][j] = 0;
        }
    }

    // заполняем матрицу B элементами из массива A
    for (i = 0; i < rows; i++) {
        for (j = 0; j < k; j++) {
            if (i * k + j < m) {
                B[i][j] = A[i * k + j];
            }
        }
    }

    // выводим матрицу B
    printf("Матрица B:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < k; j++) {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }

    // освобождаем память
    for (i = 0; i < rows; i++) {
        free(B[i]);
    }
    free(B);
}

int main() {
    int m, k, i;
    
    printf("Введите количество элементов в массиве A: ");
    scanf("%d", &m);
    int *A = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++) {
        printf("Введите элемент A[%d]: ", i);
        scanf("%d", &A[i]);
    }
    
    printf("Введите количество элементов k: ");
    scanf("%d", &k);
    
    generate_matrix(A, m, k);

    free(A);
    return 0;
}
