#include <stdio.h>
#include <math.h>

int fact(int n)
{
	if (n == 0)
	{
		return 1;
	}
	 
	else {
		int res = 1;
		for (int i = 1; i <= n; i++)
		{
			res *= i;
		}
		
		return res;	
	}
}

double taylor (double x, double eps)
{
	double trl = 1.0;
	double res = 1.0;
	int n = 1;

	while (fabs(trl) >= eps)
	{
		trl = pow (-1, n) * pow (x, 2 * n)/ fact(2 * n);
		res += trl;
		n++;
	}
	
	return res;
}


int main ()
{
	double x = 0.05;
	double eps = 0.0001;
	double taylor_cos = taylor (x, eps);
	double standard_cos = cos (x);
	
	printf("Taylor cos: %lf\n", taylor_cos);
    printf("Standard cos: %lf\n", standard_cos);
	
	return 0;
}