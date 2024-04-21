#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k;

    printf("kol-vo strok: ");
    scanf("%d", &k);

    int **tab = (int**) malloc (k * sizeof(int *));
    for (int i = 0; i < k; i++)
    {
        tab[i] = (int*) malloc (k * sizeof(int));
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            tab[i][j] = (i + 1) * (j + 1);
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < k; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;

}