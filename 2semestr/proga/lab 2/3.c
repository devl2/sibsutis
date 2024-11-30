#include <stdio.h>

void binary(int num)
{
    if (num == 0)
    {
        return;
    }

    binary (num / 2);
    printf("%d", num % 2);
}

int main ()
{   
    int num;
    printf("dec: ");
    scanf("%d", &num);

    printf("binary: ");
    binary(num);
    
    return 0;
}