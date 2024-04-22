#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int n;
    float *temp;
    printf("введите размер массива n: ");
    scanf("%d", &n);

    float *a = new float [n];
    float **b = new float *[n];

    srand(time(NULL));
     for(int i = 0; i < n; i++)
    {
        a[i] = (float) rand() / RAND_MAX * 10.0 ;
        b[i] = &a[i];
    }

    printf("массив a: ");
    for(int i = 0; i < n; i++)
    {
        printf(" %.2f", a[i]);
    }
    
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - 1; j++)
        {
            if (*b[j] > *b[j + 1])
            {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

      printf("\nмассив b: ");
        for(int i = 0; i < n; i++)
        {
            printf(" %.2f", *b[i]);
        }

 
    delete a;
    delete b;
}

