#include <stdio.h>

void positiveNum()
{
    int n;
    scanf("%d", &n);

    if (n == 0)
    {
        return;
    }

    positiveNum();

    if (n > 0)
    {
        printf("%d\n", n);
    }
    
}

int main()
{
    printf("Введите последовательность чисел: \n");
    positiveNum();

    return 0;
}