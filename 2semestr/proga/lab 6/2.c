#include <stdio.h>
#include <math.h>

const double p = 0.45;

int fact(int n)
{
    if (n == 0)
    {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

void deti(int n, int m, double *pm)
{
    double q = 1 - p;

    int cmn = fact(n) /(fact(m) * fact(n - m));

    *pm = cmn * pow(q, m) * pow (p, n - m);
}   

int main()
{
    int n, m;
    double pm;

    printf("количество детей: ");
    scanf("%d", &n);
    printf("количество мальчиков: ");
    scanf("%d", &m);

    deti(n, m, &pm);

    printf("из %d детей, %.2f мальчиков", n, pm);

    return 0;
}