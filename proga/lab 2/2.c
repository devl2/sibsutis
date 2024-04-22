#include <stdio.h>

void Numbers(int a[], int i)
{
    if (i == 7)
    {
        return;
    }
    
    if (a[i] < 0)
    {
        printf("%d ", a[i]);
    }
    
    Numbers(a, i + 1);

    if (a[i] > 0)
    {
        printf("%d ", a[i]);
    }
}

int main ()
{
    int a[] = {-3, 4, 1, 5, -2, 7, -9};
    Numbers(a, 0);
    return 0;
}