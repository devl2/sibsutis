#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <iomanip>

#include "t_alg.h"

using namespace std;

void calculation_AW(int **AW, int **VW,int size){
	for(int i = 0; i < size; i++){
		for(int j = (i + 1); j < size; j++){
			AW[i][j] = AW[i][j-1] + VW[1][j];
		}
	}
}

void calculation_APandAR(int **AP, int **AR, int **AW, int size){
	for(int i = 0; i < size - 1; i++){
		int j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for(int h = 2; h < size; h++){
		for(int i = 0; i < size - h; i++){
			int j = i + h;
			int m = AR[i][j - 1];
			int min = AP[i][m - 1] + AP[m][j];
			for(int k = m + 1; k <= AR[i + 1][j]; k++){
				int x = AP[i][k - 1] + AP[k][j];
				if(x < min){
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void createTree_PR(tree*& root, int lBorder, int rBorder, int **AR, int **VW){
	if(lBorder < rBorder){
		int k = AR[lBorder][rBorder];
    addRST_R(root, VW[0][k], VW[1][k]);
		createTree_PR(root, lBorder, k - 1, AR, VW);
		createTree_PR(root, k, rBorder, AR, VW);
	}
}

void QuickSortV2(int** A, int R, int L) {
    while (L < R) {
        int x = A[1][L];
        int i = L;
        int j = R;
        while (i <= j) {
            while (A[1][i] > x) i++;
            while (A[1][j] < x) j--;
            if (i <= j) {
                swap(A[0][i], A[0][j]);
                swap(A[1][i], A[1][j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSortV2(A, R, i);
            R = j;
        } else {
            QuickSortV2(A, j, L);
            L = i;
        }
    }
}

void A1(tree *&p, int size, int **VW) {
    QuickSortV2(VW, size - 1, 0);

    for (int i = 1; i < size; i++) {
        addRST_R(p, VW[0][i], VW[1][i]);
    }
}

void A2(tree *&p, int L, int R, int **VW) {
    int wes = 0, sum = 0;
    if (L <= R) {
        int i = 0;
        for (i = L; i < R; i++) wes += VW[1][i];

        for (i = L; i < R; i++) {
            if ((sum <= wes / 2) && (sum + VW[1][i] > wes / 2)) break;
            sum += VW[1][i];
        }

        addRST_R(p, VW[0][i], VW[1][i]);
        A2(p, L, i - 1, VW);
        A2(p, i + 1, R, VW);
    }
}

void pr_DOP(){
    const int size = 100;
    int n1 = 9;

    const int seed = time(NULL);
    srand(seed);

    int **VandW = new int*[2]; 

    for (int i = 0; i < 2; i++){
        VandW[i] = new int[size + 1];
        VandW[i][0] = 0;
    }
    
    bool table[2 * size] = {false};
    int x;
    for (int i = 1; i < size + 1; i++){
        while (table[x = rand() % (2 * size)])
        ;
        table[x] = true;
        VandW[0][i] = x;
    }

    for (int i = 1; i < size + 1; i++) {
        for (int j = size - 1 + 1; j > i; j--) {
            if (VandW[0][j] < VandW[0][j - 1]) {
                swap(&VandW[0][j], &VandW[0][j - 1]);
            }
        }
    }

    for (int i = 1; i < size + 1; i++){
        VandW[1][i] = rand() % size + 1;
    }

    short int tmp = 0;
    for (int i = 1; i < size + 1; i++){ 
        std::cout.width(3);
        std::cout << VandW[0][i];
        std::cout << "[";
        std::cout.width(2);
        std::cout << VandW[1][i]; 
        std::cout << "]" <<"  ";
        tmp++;
        if(tmp == 10){
        std::cout << std::endl;
        tmp = 0;
        }
    }
    std::cout << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    int **AW = new int*[size + 1]; // матрица весов
    int **AP = new int*[size + 1]; // матрица взвешенных высот
    int **AR = new int*[size + 1]; // матрица индексов
    
    for (int i = 0; i < size + 1; i++){
        AW[i] = new int[size + 1];
        AP[i] = new int[size + 1];
        AR[i] = new int[size + 1];
        for (int j = 0; j < size + 1; j++)
        AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }
    calculation_AW(AW, VandW, size + 1);
    calculation_APandAR(AP, AR, AW, size + 1);
    
    std::cout << "Матрица AW:" << std::endl;
    printSquareMatrix(AW, n1 + 1);
    std::cout << "Матрица AP:" << std::endl;
    printSquareMatrix(AP, n1 + 1);
    std::cout << "Матрица AR:" << std::endl;
    printSquareMatrix(AR, n1 + 1);

    tree* OST = nullptr;
    createTree(OST, 0, size, AR, VandW);
    std::cout << std::endl << "Дерево оптимального поиска (точный алгоритм)" << std::endl;
    tprint2(OST);
    std::cout << std::endl << "_____________________";
    std::cout << std::endl;
    std::cout << "Размер: " << tsize(OST) << std::endl;
    std::cout << "Сумма: " << tsum(OST) << std::endl;
    std::cout << "Сред. высота: " << avgHeight(OST) << " " << std::endl;
    std::cout << std::endl;
    std::cout << "AP[0,n] / AW[0,n] = " << (double)AP[0][size] / AW[0][size] << std::endl;
    std::cout << std::endl << std::endl;

    tree* OST_A1 = nullptr;
    tree* OST_A2 = nullptr;
    A2(OST_A2, 1, size, VandW);
    A1(OST_A1, size + 1, VandW);
    
    std::cout << std::endl << "Дерево оптимального поиска (приближенный алгоритм #1)" << std::endl;
    tprint2(OST_A1);
    std::cout << std::endl << "_____________________";
    std::cout << std::endl;
    std::cout << "Размер: " << tsize(OST_A1) << std::endl;
    std::cout << "Сумма: " << tsum(OST_A1) << std::endl;
    std::cout << "Сред. высота: " << avgHeight(OST_A1) << " " << std::endl;
    std::cout << std::endl;

    std::cout << std::endl << "Дерево оптимального поиска (приближенный алгоритм #2)" << std::endl;
    tprint2(OST_A2);
    std::cout << std::endl << "_____________________";
    std::cout << std::endl;
    std::cout << "Размер: " << tsize(OST_A2) << std::endl;
    std::cout << "Сумма: " << tsum(OST_A2) << std::endl;
    std::cout << "Сред. высота: " << avgHeight(OST_A2) << " " << std::endl;
    std::cout << std::endl;


        cout << endl << endl;
        cout << "   n=100  |  Размер   |  Контр. сумма  | Высота   |  Средневзвеш.высота  |" << endl;
        for (int q = 100; q < 101; q += 100) {
            cout << "     ДОП  " << "|" << tsize(OST) << "   |    " << tsum(OST) << "\t       |   " << theight(OST) << "            |" << avgHeight(OST) << "               |" << endl;
            cout << "     A1  " << "|" << tsize(OST_A1) << "   |    " << tsum(OST_A1) << "\t       |   " << theight(OST_A1) << "            |" << avgHeight(OST_A1) << "               |" << endl;
            cout << "     A2  " << "|" << tsize(OST_A2) << "   |    " << tsum(OST_A2) << "\t       |   " << theight(OST_A2) << "            |" << avgHeight(OST_A2) << "               |" << endl;
        }
}


