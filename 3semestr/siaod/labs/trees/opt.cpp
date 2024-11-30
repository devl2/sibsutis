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
    tree* L = nullptr;
    tree* R = nullptr;
};

void calculation_AW(int **AW, int **VW,int size){
	for(int i = 0; i < size; i++){
		for(int j = (i + 1); j < size; j++){
			AW[i][j] = AW[i][j-1] + VW[1][j];
		}
	}
}

/* Вычисление матрицы взвешенных высот (AP) и матрицы индексов (AR) */
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

void addRST_R(tree *&p, int data, int weight) {
  if (p == NULL) {
    p = new tree;
    p -> data = data;
    p -> weight = weight;
  } else if (data < p->data)
    addRST_R(p -> L, data, weight);
  else if (data > p -> data)
    addRST_R(p -> R, data, weight);
}

/* Создание дерева */
void createTree(tree*& root, int lBorder, int rBorder, int **AR, int **VW){
	if(lBorder < rBorder){
		int k = AR[lBorder][rBorder];
        addRST_R(root, VW[0][k], VW[1][k]);
		createTree(root, lBorder, k - 1, AR, VW);
		createTree(root, k, rBorder, AR, VW);
	}
}

void tprint2(tree* p) {
    if (p == nullptr) return;
    tprint2(p->L);
    cout << p->data << " ";
    tprint2(p->R);
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void QuickSortV2(int** A, int R, int L)
{
    while (L < R) {
        int x = A[1][L];
        int i = L;
        int j = R;
        while (i <= j) {
            while (A[1][i] > x)
                i++;
            while (A[1][j] < x)
                j--;
            if (i <= j) {
				swap(&A[0][i], &A[0][j]);
                swap(&A[1][i], &A[1][j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSortV2(A, R, i);
            R = j;
        }
        else {
            QuickSortV2(A, j, L);
            L=i; 
        } 
    } 
}

void A1(tree *&p, int size, int **VW)
{
	QuickSortV2(VW,size-1, 0);

	short int tmp = 0;
	for (int i = 1; i < size; i++){ 
		std::cout.width(3);
		std::cout << VW[0][i];
		std::cout << "[";
		std::cout.width(2);
		std::cout << VW[1][i]; 
		std::cout << "]" <<"  ";
		tmp++;
		if(tmp == 10){
			std::cout << std::endl;
			tmp = 0;
		}
	}
	for(int i = 1; i < size; i++)
	{
		addRST_R(p, VW[0][i], VW[1][i]);
	}
}

void A2(tree *&p, int L, int R, int **VW)
{
	int wes = 0, sum = 0;
	if(L <= R)
	{
		int i = 0;
		for(i = L; i < R; i++)
			wes = wes + VW[1][i];
		

		for(i = L; i < R; i++)
		{
			if((sum <= wes / 2) && (sum + VW[1][i] > wes / 2))
				break;
			sum = sum + VW[1][i];
		}
		
		addRST_R(p, VW[0][i], VW[1][i]);
		A2(p, L, i - 1, VW);
		A2(p, i + 1, R, VW);
	}
}

void printSquareMatrix (int **arr, int size){
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      std::cout.width(5);
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
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

int main(int argc, const char **argv) {
    const int size = 100;
    srand(time(nullptr));

    int **VandW = new int*[2];  // Данные и их веса

    for (int i = 0; i < 2; i++) {
        VandW[i] = new int[size + 1];
        VandW[i][0] = 0;
    }

    // Заполнение вершин неповторяющимися числами 
    bool table[2 * size] = {false};
    int x;
    for (int i = 1; i < size + 1; i++) {
        while (table[x = rand() % (2 * size)]);
        table[x] = true;
        VandW[0][i] = x;
    }

    // Сортировка вершин
    sort(VandW[0] + 1, VandW[0] + size + 1);

    // Случайные веса для вершин
    for (int i = 1; i < size + 1; i++) {
        VandW[1][i] = rand() % size + 1;
    }

    // Вывод начальных данных и весов
    short int tmp = 0;
    for (int i = 1; i < size + 1; i++) {
        cout.width(3);
        cout << VandW[0][i];
        cout << "[";
        cout.width(2);
        cout << VandW[1][i]; 
        cout << "]  ";
        tmp++;
        if (tmp == 10) {
            cout << endl;
            tmp = 0;
        }
    }
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    // Инициализация и заполнение матриц
    int **AW = new int*[size + 1];
    int **AP = new int*[size + 1];
    int **AR = new int*[size + 1];
    for (int i = 0; i < size + 1; i++) {
        AW[i] = new int[size + 1];
        AP[i] = new int[size + 1];
        AR[i] = new int[size + 1];
        for (int j = 0; j < size + 1; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }

    // Вызов функций для заполнения матриц AW, AP и AR
    calculation_AW(AW, VandW, size + 1);
    calculation_APandAR(AP, AR, AW, size + 1);

    // Печать матриц, если размер небольшой
    cout << "Матрица AW:" << endl;
    printSquareMatrix(AW, size + 1);
    cout << "Матрица AP:" << endl;
    printSquareMatrix(AP, size + 1);
    cout << "Матрица AR:" << endl;
    printSquareMatrix(AR, size + 1);

    // Создание дерева оптимального поиска
    tree* OST = nullptr;
    createTree(OST, 0, size, AR, VandW);
    cout << endl << "Дерево оптимального поиска (точный алгоритм)" << endl;
    tprint2(OST);
    cout << endl << "_____________________" << endl;
    cout << tsize(OST) << endl;
    cout << tsum(OST) << endl;
    cout << avgHeight(OST) << endl;
    cout << "AP[0,size] / AW[0,size] = " << (double)AP[0][size] / AW[0][size] << endl;

    // Приближенные деревья
    tree* OST_A1 = nullptr;
    tree* OST_A2 = nullptr;
    A2(OST_A2, 1, size, VandW);
    A1(OST_A1, size + 1, VandW);

    cout << endl << "Дерево оптимального поиска (приближенный алгоритм #1)" << endl;
    tprint2(OST_A1);
    cout << endl << "_____________________" << endl;
    cout << tsize(OST_A1) << endl;
    cout << tsum(OST_A1) << endl;
    cout << avgHeight(OST_A1) << endl;

    cout << endl << "Дерево оптимального поиска (приближенный алгоритм #2)" << endl;
    tprint2(OST_A2);
    cout << endl << "_____________________" << endl;
    cout << tsize(OST_A2) << endl;
    cout << tsum(OST_A2) << endl;
    cout << avgHeight(OST_A2) << endl;

    // Очистка памяти
    for (int i = 0; i < size + 1; i++) {
        delete[] AW[i];
        delete[] AP[i];
        delete[] AR[i];
    }
    delete[] AW;
    delete[] AP;
    delete[] AR;
    delete[] VandW[0];
    delete[] VandW[1];
    delete[] VandW;

    return 0;
}

