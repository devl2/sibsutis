#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void FillAlf(int n, char a[]) {
    for (int i = 0; i < n; i++) {
        a[i] = 'A' + (char)i;
    }
}

void FillInc(int n, int a[]) {
  for (int i = 1; i < n + 1; i++) {
    a[i] = i;
  }
}

void FillDec(int n, int a[]) {
  for (int i = 0; i < n; i++) {
    a[(n - 1) - i] = i;
  }
}

void FillRand(int n, int a[]) {
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 10;
  }
}

void CheckSum(int n, int a[]) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += a[i];
  }
  printf(" - summ: %d", sum);
}

void RunNumber(int n, int a[]) {
  int k = 1, j = 0;
  a[n] = -1;

  for (int i = 0; i < n; i++) {
    if (a[i + 1] < a[i]) {
      j++;
    }
  }
  printf("; kol-vo serie: %d; ", j);
}

void PrintMas(int n, int a[]) {
  for (int i = 0; i < n; i++) {
    printf("%d", a[i]);
  }
}

void PrintMasAlf(int n, char a[]){
    for (int i = 0; i < n; i++) {
        printf("%c ", a[i]);
    }
}

void SelectSort(int n, int a[]) {
  int j, min, t, c = 0, m = 0,b[n];
  
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
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
  printf("     M+C: %6d     ", c + m);
}

void BubbleSort(int n, int a[]) {
  int t, c = 0, m = 0,b[n];
  
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }
  
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j >= i + 1; j--) {
      c++;
      if (b[j] < b[j - 1]) {
        t = b[j];
        b[j] = b[j - 1];
        b[j - 1] = t;
        m += 3;
      }
    }
  }
  //printf("s: %6d; m: %6d;", c, m);
  printf("     M+C: %6d     ", c + m);
}

void ShakerSort(int n, int a[]) {
  int t, c = 0, m = 0, l = 0, r = (n - 1), k = (n - 1),b[n];
  
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }
  
  while (l < r) {
    for (int i = r; i > l; i--) {
      c++;
      if (b[i] < b[i - 1]) {
        t = b[i];
        b[i] = b[i - 1];
        b[i - 1] = t;
        k = i;
        m += 3;
      }
    }
    l = k;
    for (int i = l; i < r; i++) {
      c++;
      if (b[i] > b[i + 1]) {
        t = b[i];
        b[i] = b[i + 1];
        b[i + 1] = t;
        k = i;
        m += 3;
      }
    }
    r = k;
  }
  //printf("s: %6d; m: %6d;", c, m);
  printf("     M+C: %6d     ", c + m);
}

void InsertSort(int n, int a[]) {
    
  int t, j, c = 0, m = 0,b[n];
  
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }
  
  for (int i = 1; i < n; i++,c++) {
    t = b[i];
    m++;
    j = i - 1;
    for (; j >= 0 && t < b[j];m++,j--) {
        b[j + 1] = b[j];
        if (j != 0){
            c++;
        }
    }
    b[j + 1] = t;
    m++;
  }
  
  //printf("s: %6d; m: %6d;", c, m);
  printf("     M+C: %6d     ", c + m);
}

void dv(int n, int a[], int x){
    int l = 0, r = n, m = 0, nai = 0, s = 0;
    while (l + 1 <= r){
        m = (l + r) / 2;
        s++;
        if (a[m] == x){
            nai = m;
            break;
        }
        s++;
        if (a[m] < x){
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    printf("          %2d         ", s);
}

void dv2(int n, int a[], int x){
    int l = 0, r = n, m, nai = -1, s = 0;
    while (l < r){
        m = (l + r) / 2;
        s++;
        if (a[m] < x){
            l = m + 1;
        } else {
            r = m;
        }
    }
    s++;
    if (a[r] == x){
        printf("          %2d         ", s);
    }
    // else {
    //     printf("Не найден");
    // }
}

void quicksort(int n, int a[])
{
    int l = 0, r = 0, i = l, j = r, x = a[l];
    while (i <= j)
    {
      while(a[i] < x)
      {
        i++;
      }

      while (a[j] < x)
      {
        j--;
      }

      if (i <= j)
      {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
      }
    }

    
}

int main() {
    srand(time(NULL));
    
    int n = 100;
    srand(time(NULL));
    int x = 100;
    printf(" _____________________________________________________\n");
    printf("|  N   |     С(ф) I Версия     |     С(ф) II Версия    |\n");
    printf("|______|_______________________|_______________________|\n");
    printf("|      |                       |                       |\n");
    while (n != 1100) {
        int a[n];
        printf("| %4d |",n);
        printf(" ");
        FillInc(n,a);
        dv(n, a, x);
        printf(" | ");
        FillInc(n,a);
        dv2(n, a, x);
        printf(" |\n");
        n+=100;
    }
        printf("|______|_______________________|_______________________|\n");
        
    return 0;
}