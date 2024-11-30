#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int f(int n)
{
    int a, b, c, d, e, f ;
    
    a = n % 19;
    b = n % 4;
    c = n % 7;
    d = (19*a + 15) % 30;
    e = (2*b +4*c + 6*d + 6) % 7;
    f = d + e;
    
    if (f <= 26) {
		printf("%d april",f + 4);
	} 
		else {
            printf("%d may", f - 26);
        }

    return 0;
}

int main()
{
    int n;
    scanf("%d",&n);
    f(n);
    
    return 0;
}
