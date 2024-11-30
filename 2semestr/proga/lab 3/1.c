#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    int n, m, k;
    printf("введите размер массива: ");
    scanf("%d", &n);
    int *b = (int * ) malloc(n * sizeof(int));
    if (b == NULL)
    {
        printf("не выделена память");
        return 1;
    }

    srand(time(NULL));
    printf("массив b: ");
    for (int i = 0; i < n; i++)
    {
       b[i] = rand() % 101 - 50;
       printf("%d ", b[i]);
    }

    for (int i = 0; i < n; i++)
    {
        if (b[i] > 0)
        {
            m++;
        } else if (b[i] < 0)
             {
                 k++;
             }
    }

    int *c = (int * ) malloc(m * sizeof(int));
    int *d = (int * ) malloc(k * sizeof(int));

    if (c == NULL || d == NULL)
    {
        printf("ошибка выделения памяти");
        free (b);
        if (c != NULL) free (c);
        if (d != NULL) free (d);
        return 1;
    }

    int c1 = 0, d1 = 0; 
    for (int i = 0; i < n; i++)
    {
        if (b[i] > 0)
        {
            c[c1++] = b[i];
            
        }else if (b[i] < 0)
        {
            d[d1++] = b[i];
        }
    }

    printf("\nмассив с положительными числами: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d ", c[i]);
    }

    printf("\nмассив с отрицательными числами: ");
    for (int i = 0; i < k; i++)
    {
        printf("%d ", d[i]);
    }

    free (b);
    free (c);
    free (d);

    return 0;
}