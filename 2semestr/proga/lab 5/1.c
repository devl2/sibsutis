#include <stdio.h>
#include <stdlib.h>

int *create_mas(int m) {
    int *a = (int *)malloc(m * sizeof(int));
    for(int i = 0; i < m; i++) 
    {
        a[i] = rand() % 100;
    }
    return a;
}

void print_mas(int *mas, int m) 
{
    for(int i = 0; i < m; i++) 
    {
        printf("%d ", mas[i]);
    }
    printf("\n");
}

int **create_matrix(int *a, int m, int k) 
{
    int strk = m / k;
    if (m % k != 0) 
    {
        strk++;
    }

    int **b = (int **)malloc(strk * sizeof(int *));
    for(int i = 0; i < strk; i++) 
    {
        b[i] = (int *) malloc (k * sizeof(int));
        for (int j = 0; j < k; j++) 
        {
            if(i * k + j < m) 
            {
                b[i][j] = a[i * k + j];
            } 
            else 
            {
                b[i][j] = 0;
            }
        }
    }
    return b;
}

int main() 
{
    int m, k;

    printf("m = ");
    scanf("%d", &m);

    printf("k = ");
    scanf("%d", &k);

    int *a = create_mas(m);
    printf("matrix a: ");
    print_mas(a, m);

    int **b = create_matrix(a, m, k);
    printf("matrix b: \n");
    int strk = m / k + (m % k != 0);
    for (int i = 0; i < strk; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

   
    for (int i = 0; i < m / k + (m % k != 0); i++) 
    {
        free(b[i]);
    }
    free(b);
    free(a);

    return 0;
}
