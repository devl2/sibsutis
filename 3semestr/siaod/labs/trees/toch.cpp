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

void matrixAW(int** AW, int* W, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            AW[i][j] = AW[i][j - 1] + W[j];
        }
    }
    cout << "matrixAW calculation completed." << endl;  // Debug output
}

void calcAP_AR(int** AP, int** AR, int** AW, int n) {
    for(int i = 0; i < n - 1; i++) {
        int j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for(int h = 2; h < n; h++) {
        for(int i = 0; i < n - h; i++) {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];
            for(int k = m + 1; k <= AR[i + 1][j]; k++) {
                int x = AP[i][k - 1] + AP[k][j];
                if(x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
    cout << "calcAP_AR calculation completed." << endl;  // Debug output
}

void add(tree*& p, int data, int weight) {
    if (p == nullptr) {
        p = new tree;
        p->data = data;
        p->weight = weight;
    } else if (data < p->data) {
        add(p->L, data, weight);
    } else if (data > p->data) {
        add(p->R, data, weight);
    }
}

void createTree(tree*& p, int lBorder, int rBorder, int** AR, int** VW) {
    if (lBorder <= rBorder) {
        int k = AR[lBorder][rBorder];
        add(p, VW[0][k], VW[1][k]);
        createTree(p, lBorder, k - 1, AR, VW);
        createTree(p, k + 1, rBorder, AR, VW);
    }
    cout << "createTree completed for borders: " << lBorder << ", " << rBorder << endl;  // Debug output
}

void tprint2(tree* p) {
    if (p == nullptr) return;
    tprint2(p->L);
    cout << p->data << " ";
    tprint2(p->R);
}

int main() {
    const int size = 10;  // Уменьшим размер для тестирования
    srand(time(nullptr));

    // Инициализация данных
    int **VandW = new int*[2];
    for (int i = 0; i < 2; i++) {
        VandW[i] = new int[size + 1];
        VandW[i][0] = 0;
    }

    // Заполнение значениями
    bool table[2 * size] = {false};
    int x;
    for (int i = 1; i <= size; i++) {
        while (table[x = rand() % (2 * size)]);
        table[x] = true;
        VandW[0][i] = x;
    }
    sort(VandW[0] + 1, VandW[0] + size + 1);

    for (int i = 1; i <= size; i++) {
        VandW[1][i] = rand() % size + 1;
    }

    cout << "VandW initialized." << endl;  // Debug output

    // Инициализация матриц
    int **AW = new int*[size + 1];
    int **AP = new int*[size + 1];
    int **AR = new int*[size + 1];
    for (int i = 0; i <= size; i++) {
        AW[i] = new int[size + 1];
        AP[i] = new int[size + 1];
        AR[i] = new int[size + 1];
        for (int j = 0; j <= size; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;
    }

    matrixAW(AW, VandW[1], size + 1);  // Debug output inside function
    calcAP_AR(AP, AR, AW, size + 1);   // Debug output inside function

    tree* OST = nullptr;
    createTree(OST, 0, size, AR, VandW);
    cout << "Optimal search tree created." << endl;  // Final Debug output

    cout << "Дерево оптимального поиска (точный алгоритм)" << endl;
    tprint2(OST);  // Print to check tree output
    cout << endl;

    // Освобождение памяти
    for (int i = 0; i <= size; i++) {
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
