#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int step(float x, int n)
{
    float y=1;
    if (n > 0){
        for (int i = 0; i < n; i++)
        {
            y = x*y;
        }
        
    }
    if (n < 0){
        for (int i = 0; i > n; i--)
        {
            y *= (1/x);
        }
        
    }
    
    if (n == 0)
	{ 
		y = 1;
	}
	
    printf ("%.2f",y);
    
    return 0;
}


int main()
{
    int n;
    float x;
    scanf("%f",&x);
    scanf("%d",&n);
    step(x,n);
    return 0;
}
