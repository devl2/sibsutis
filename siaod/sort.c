#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - 1 - i;
    }
}

void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

void SelectSort(int A[], int n) {
    int j, min, t, c = 0, m = 0,b[n];
  
    for (int i = 0; i < n; i++) {
        b[i] = A[i];
    }
  
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            c++;
            if (b[j] < b[min]) {
                min = j;
            }
        }
        if (min != i) {
            t = b[min];
            b[min] = b[i];
            b[i] = t;
            m += 3;
        }
    }
    printf("  %7d      |", c + m);
}

void BubbleSort(int A[], int n) {
    int sr = 0, per = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                int k = A[j];
                A[j] = A[j - 1];
                A[j - 1] = k;
                per += 3;
            }
            sr += 1;
        }
    }
    printf("      %6d        | ", per + sr);
}

void ShakerSort(int A[], int n) {
    int sr = 0, per = 0;
    int left = 0, right = n - 1;

    while (left < right) {
        for (int i = left; i < right; i++) {
            sr++;
            if (A[i] > A[i + 1]) {
                int tmp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = tmp;
                per += 3; 
            }
        }
        right--;

        for (int i = right; i > left; i--) {
            sr++;
            if (A[i] < A[i - 1]) {
                int tmp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = tmp;
                per += 3;
            }
        }
        left++;
    }
    printf("   %7d     | ", per + sr);
}

void InsertSort(int A[], int n)
{
    int sr = 0, per = 0;
    int temp;

    for (int i = 1; i < n; i++)
    {   
        sr++;
        for (int j = i; j > 0 && A[j - 1] > A[j]; j--)
        {
            temp = A[j-1];
            A[j-1] = A[j];
            A[j] = temp;
            per += 2; 
        }
        sr++;
    }
    printf("    %7d         |", sr + per);
}

void ShellSort(int A[], int n) {
    int s, i, j, temp, per = 0, sr = 0;

    for (s= n / 2; s > 0; s /= 2) {
        sr++;
        for (i = s; i < n; i++) {
            sr++;
            for (j = i - s; j >= 0 && A[j] > A[j + s]; j -= s) {
                per++;
                temp = A[j];
                A[j] = A[j + s];
                A[j + s] = temp;
            }
        }
    }
    printf("     %7d       |", per + sr);
}

void calcInsertSortFormula(int n)
{
    int Mmax, Cmax;

    Cmax = ((n * n) - n) / 2;
    Mmax = Cmax + ((2 * n) - 2);
    
    printf("  %6d    |", Mmax + Cmax); 
}

void KnutFormula(int n)
{
    int h = 1;
    while (h < n)
    {
        h = 2 * h + 1;
    }
    printf("    %7d           |", h);
}


int main() {
    printf("--------------------------------------------------------------------------------\n");
    printf("|    N    |    h1 ... hm (Knut)  |    Shell(M+C)    |      Insert (M+C)     |\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int n = 100; n <= 500; n += 100) {
        printf("| %7d |", n);

        int A[n];

        FillRand(A, n);
        KnutFormula(n);

        ShellSort(A, n);
        InsertSort(A, n);
        
        printf("\n");
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("\n");

    return 0;
}
