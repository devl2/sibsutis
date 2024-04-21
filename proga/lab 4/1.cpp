#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int n = 5;

int **creatematrix(int m, int n)
{
    int **matrix = new int *[m];
    for (int i = 0; i < m; i++)
    {
        matrix[i] = new int[n];
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
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int m;
    printf("введите число строк: ");
    scanf("%d", &m);

    srand(time(NULL));

    int **B = creatematrix(m, n);
    printf("матрица B:\n");
    print_matrix(B, m, n);

    int max_el = B[0][0], max_i = 0, max_j = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (B[i][j] > max_el)
            {
                max_el = B[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    printf("\nмаксимальный элемент: %d\n", max_el);

    int **C = new int *[m - 1];
    for (int i = 0; i < m - 1; i++)
    {
        C[i] = new int [n - 1];
    }

    int str = 0, stb = 0;
    for (int i = 0; i < m; i++)
    {
        if (i == max_i)
            continue;
        for (int j = 0; j < n; j++)
        {
            if (j == max_j)
                continue;
            C[str][stb++] = B[i][j];
        }
        stb = 0;
        str++;
    }

    printf("\nматрица С:\n");
    print_matrix(C, m - 1, n - 1);

    for (int i = 0; i < m; i++)
    {
        delete [] B;
    }
    delete [] B;

    for (int i = 0; i < m - 1; i++)
    {
        delete [] C;
    }
    delete [] C;
    return 0;
}
