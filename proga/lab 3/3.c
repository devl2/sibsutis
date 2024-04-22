#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("введите n: ");
    scanf("%d", &n);
    int *al = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 2; i <= n; i++)
    {
        al[i] = 0;
    }

    for (int i = 2; i * i <= n; i++)
    {
        for (int s = i * i; s <= n; s += i)
        {
            al[s] = 1;
        }
    }

    printf("простые числа от 2 до %d:\n", n);
    for (int i = 2; i <= n; i++)
    {
        if (al[i] == 0)
        {
            printf("%d ", i);
        }
    }

    free(al);
    return 0;
}
