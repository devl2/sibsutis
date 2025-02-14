#include <iostream>
#include <ctime>
#include <iomanip>

const int n = 3; // строки (уравнения)
const int m = n + 1; // столбцы (коэффициенты + свободные члены)

void printMatrix(double** matr) {
    std::cout << "\n";
    std::cout << "Матрица:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::fixed << std::setprecision(2)<< matr[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void gauss(double** matr) {
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            double kof = matr[j][i]/matr[i][i];
                for (int u = 0; u < m; u++){
                    matr[j][u] -= kof * matr[i][u];
                }
        }
        std::cout << "Шаг " << i + 1 << ":";
        printMatrix(matr);
    }

    double x[n];
    for (int i = n - 1; i >= 0; i--) {
        x[i] = matr[i][m - 1];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matr[i][j] * x[j];
        }
        x[i] /= matr[i][i];
    }

    std::cout << "Решение системы:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "x" << i + 1 << " = " << x[i] << "\n";
    }
}

int main() {
    srand(time(NULL));
    double** matr = new double* [n];
    for (int i = 0; i < n; i++) {
        matr[i] = new double[m];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matr[i][j] = (rand() % 5 + 1);
        }
    }
    
    printMatrix(matr);

    gauss(matr);

    for (int i = 0; i < n; i++) {
        delete[] matr[i];
    }
    delete[] matr;

    return 0;
}
