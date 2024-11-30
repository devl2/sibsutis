#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

struct tree {
    int data;
    int weight;
    int index;
    tree* L = nullptr;
    tree* R = nullptr;
};

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void matrixW(int** W1, int** VW, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = (i + 1); j < size; j++) {
            W1[i][j] = W1[i][j - 1] + VW[1][j];
        }
    }
}

void matrixPr(int** P1, int** r1, int** W1, int size) {
    for (int i = 0; i < size - 1; i++) {
        int j = i + 1;
        P1[i][j] = W1[i][j];
        r1[i][j] = j;
    }
    for (int h = 2; h < size; h++) {
        for (int i = 0; i < size - h; i++) {
            int j = i + h;
            int m = r1[i][j - 1];
            int min = P1[i][m - 1] + P1[m][j];
            for (int k = m + 1; k <= r1[i + 1][j]; k++) {
                int x = P1[i][k - 1] + P1[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            P1[i][j] = min + W1[i][j];
            r1[i][j] = m;
        }
    }
}

void addRST_R(tree*& p, int data, int weight) {
    if (p == NULL) {
        p = new tree;
        p->data = data;
        p->weight = weight;
    }
    else if (data < p->data)
        addRST_R(p->L, data, weight);
    else if (data > p->data)
        addRST_R(p->R, data, weight);
}

void createTree(tree*& root, int Lb, int Rb, int** r1, int** VW) {
    if (Lb < Rb) {
        int k = r1[Lb][Rb];
        addRST_R(root, VW[0][k], VW[1][k]);
        createTree(root, Lb, k - 1, r1, VW);
        createTree(root, k, Rb, r1, VW);
    }
}

void add_arr(int arr[], int n) {
    srand(time(NULL));
    int* check = new int[n];
    for (int h = 0; h < n; h++) {
        check[h] = -1;
    }
    for (int i = 0; i < n; i++) {
        int temp = rand() % (n * 10);
        bool check_element = true;
        for (int j = 0; j < n; j++) {
            if (check[j] == temp) {
                check_element = false;
            }
        }
        if (check_element == true) {
            arr[i] = temp;
            check[i] = temp;
        }
        else {
            i--;
        }
    }
}

void tprint2(tree* p) {
    if (p == nullptr) return;
    tprint2(p->L);
    cout << p->data << " ";
    tprint2(p->R);
}

void printSquareMatrix(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout <<  setw(4) << arr[i][j] << "|";
        }
        cout << endl;
    }
}
int tsize(tree* p) {
    if (p == nullptr) return 0;
    return 1 + tsize(p->L) + tsize(p->R);
}

int tsum(tree* p) {
    if (p == nullptr) return 0;
    return p->data + tsum(p->L) + tsum(p->R);
}

int theight(tree* p) {
    if (p == nullptr) return 0;
    return 1 + std::max(theight(p->L), theight(p->R));
}

double sdp(tree* p, int l) {
    if (p == nullptr) return 0;
    return l + sdp(p->L, l + 1) + sdp(p->R, l + 1);
}

double avgHeight(tree* p) {
    return sdp(p, 1) / tsize(p);
}

void t_DOP(){
    int x;
    srand(time(NULL));
    const int n = 100;
    const int n1 = 9;
    int** VandW = new int* [2];

    for (int i = 0; i < 2; i++) {
        VandW[i] = new int[n + 1];
        VandW[i][0] = 0;
    }

    bool table[n] = { false };
    for (int i = 1; i < n + 1; i++) {
        while (table[x = rand() % n]);
        table[x] = true;
        VandW[0][i] = x;
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = n - 1 + 1; j > i; j--) {
            if (VandW[0][j] < VandW[0][j - 1]) {
                swap(&VandW[0][j], &VandW[0][j - 1]);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        VandW[1][i] = rand() % n + 1;
    }

    int** W = new int* [n1 + 1];
    int** P = new int* [n1 + 1]; 
    int** r = new int* [n1 + 1];

    for (int i = 0; i < n1 + 1; i++) {
        W[i] = new int[n1 + 1];
        P[i] = new int[n1 + 1];
        r[i] = new int[n1 + 1];
        for (int j = 0; j < n1 + 1; j++)
            W[i][j] = P[i][j] = r[i][j] = 0;
    }
    matrixW(W, VandW, n1 + 1);
    matrixPr(P, r, W, n1 + 1);

    short int tmp = 0;

    cout << endl << "Вывод начальных данных и весов:" << endl;
    for (int i = 1; i < n + 1; i++) {
        cout << setw(2);
        cout << VandW[0][i];
        cout << "[";
        cout << setw(3);
        cout << VandW[1][i];
        cout << "] |" << "  ";
        tmp++;
        if (tmp == 10) {
            cout << endl;
            tmp = 0;
        }
    }

    cout << endl;

    int** W1 = new int* [n + 1];
    int** P1 = new int* [n + 1]; 
    int** r1 = new int* [n + 1]; 

    for (int i = 0; i < n + 1; i++) {
        W1[i] = new int[n + 1];
        P1[i] = new int[n + 1];
        r1[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++)
            W1[i][j] = P1[i][j] = r1[i][j] = 0;
    }
    matrixW(W1, VandW, n + 1);
    matrixPr(P1, r1, W1, n + 1);

    cout << "Матрица весов W:" << endl;
    printSquareMatrix(W1, n1 + 1);
    cout << endl;

    cout << "Матрица взвешенных высот P:" << endl;
    printSquareMatrix(P1, n1 + 1);
    cout << endl;

    cout << "Матрица корней поддеревьев r:" << endl;
    printSquareMatrix(r1, n1 + 1);
    cout << endl;

    tree* DOP = nullptr;
    createTree(DOP, 0, n, r1, VandW);
    cout << "Обход слева направо:" << endl;
    tprint2(DOP);
    cout << endl << endl << "Размер: " << tsize(DOP) << endl;
    cout << "Контр. сумма: " << tsum(DOP) << endl;
    cout << "Средневзвеш.высота: " << avgHeight(DOP) << endl;
    cout << "P1[0,n] / W1[0,n] = " << (double)P1[0][n] / W1[0][n] << endl;
    cout << endl << endl;
    cout << "   n=100  |  Размер   |  Контр. сумма  | Высота   |  Средневзвеш.высота  |" << endl;
    for (int q = 100; q < 101; q += 100) {
        cout << "   ДОП  " << "  |  " << tsize(DOP) << "    |     " << tsum(DOP) << "\t        |" << theight(DOP) << "         |" << avgHeight(DOP) << "               |" << endl;
    }
}