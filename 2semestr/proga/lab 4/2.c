#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int **creatematrix(int m, int n)
{
    int **matrix = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        matrix[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void print_matrix(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int m, n;
    printf("введите число строк: ");
    scanf("%d", &m);
    printf("введите число столбцов: ");
    scanf("%d", &n);

    srand(time(NULL));

    int **A = creatematrix(m, n);
    printf("матрица A:\n");
    print_matrix(A, m, n);

    int **D = malloc((m + 1) * sizeof(int *));
    for (int i = 0; i < m + 1; i++)
    {
        D[i] = malloc((n + 1) * sizeof(int));
    }

    int sum = 0;
    for(int i = 0; i < m; i++)
    {
        int str_sum = 0;
        for(int j = 0; j < n; j++)
        {
            D[i][j] = A[i][j];
            str_sum += A[i][j];
        }
        D[i][n] = str_sum;
    }
    
    for(int j = 0; j < n; j++)
    {
        int stb_sum = 0;
        for(int i = 0; i < m; i++)
        {
            stb_sum += A[i][j];
        }
        D[m][j] = stb_sum;
    }

    for(int i = 0; i < m; i++)
    {
        sum += D[i][n];
    }

    for(int j = 0; j < n; j++)
    {
        sum += D[m][j];
    }
    
    D[m][n] = sum;
    
    printf("\n");

    printf("массив D: \n");
    print_matrix(D, m + 1, n + 1);

    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < m + 1; i++) {
        free(D[i]);
    }
    free(D);

    return 0;
}