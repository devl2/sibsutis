#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPSILON = 1e-4;

void printMatrix(double** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << setprecision(4) << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double calcMaxC(double** C, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        double rowSum = 0.0;
        for (int j = 0; j < n; j++) {
            rowSum += abs(C[i][j]);
        }
        if (rowSum > norm) {
            norm = rowSum;
        }
    }
    return norm;
}

double calcMaxB(double* B, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        if (abs(B[i]) > norm) {
            norm = abs(B[i]);
        }
    }
    return norm;
}

void simpleIterationMethod(double** A, double* B, double* x, int n) {
    double** C = new double*[n];
    double* D = new double[n];

    for (int i = 0; i < n; i++) {
        C[i] = new double[n];
        D[i] = B[i] / A[i][i];
        for (int j = 0; j < n; j++) {
            if (i == j) {
                C[i][j] = 0;
            } else {
                C[i][j] = A[i][j] / A[i][i];
            }
        }
    }

    cout << "Матрица C:" << endl;
    printMatrix(C, n);

    double maxC = calcMaxC(C, n);
    cout << "Норма матрицы C (‖𝐶‖∞): " << maxC << endl;

    double normD = calcMaxB(D, n);
    cout << "Норма вектора D (‖𝐷‖∞): " << normD << endl;

    double ch = log((EPSILON * (1 - maxC)) / normD);
    double zn = log(maxC);
    int N_calc = (ch / zn) + 1;

    cout << "Вычисленное количество итераций N: " << N_calc << endl;

    double* x_new = new double[n];
    int iteration = 0;
    cout << "Шаги метода простых итераций:" << endl;
    for (int k = 0; k < N_calc; k++) {
        for (int i = 0; i < n; i++) {
            x_new[i] = D[i];
            for (int j = 0; j < n; j++) {
                x_new[i] += C[i][j] * x[j];
            }
        }
        for (int i = 0; i < n; i++) {
            x[i] = x_new[i];
        }
        cout << "Шаг " << ++iteration << ": ";
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] C[i];
    }
    delete[] C;
    delete[] D;
    delete[] x_new;
}

// Метод Зейделя
void seidelMethod(double** A, double* B, double* x, int n) {
    double** C = new double*[n];
    double* D = new double[n];

    for (int i = 0; i < n; i++) {
        C[i] = new double[n];
        D[i] = B[i] / A[i][i];
        for (int j = 0; j < n; j++) {
            if (i == j) {
                C[i][j] = 0;
            } else {
                C[i][j] = A[i][j] / A[i][i];
            }
        }
    }

    double maxC = calcMaxC(C, n);
    double normB = calcMaxB(D, n);
    double ch = log((EPSILON * (1 - maxC)) / normB);
    double zn = log(maxC);
    int N_calc = (ch / zn) + 1;

    int iteration = 0;
    cout << "\nШаги метода Зейделя:" << endl;
    for (int k = 0; k < N_calc; k++) {
        for (int i = 0; i < n; i++) {
            double sum = D[i];
            for (int j = 0; j < i; j++) {
                sum += C[i][j] * x[j];
            }
            for (int j = i + 1; j < n; j++) {
                sum += C[i][j] * x[j];
            }
            x[i] = sum;
        }
        cout << "Шаг " << ++iteration << ": ";
        for (int i = 0; i < n; i++) {
            cout << x[i] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] C[i];
    }
    delete[] C;
    delete[] D;
}

int main() {
    const int n = 3;
    double A[n][n] = {
        {5, -1, 2},
        {-2, -10, 3},
        {1, 2, 5}
    };

    double B[n] = {3, -4, 12};

    double x_simple[n] = {0.0, 0.0, 0.0};
    double x_seidel[n] = {0.0, 0.0, 0.0};

    double** A_dynamic = new double*[n];
    for (int i = 0; i < n; i++) {
        A_dynamic[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A_dynamic[i][j] = A[i][j];
        }
    }

    simpleIterationMethod(A_dynamic, B, x_simple, n);

    seidelMethod(A_dynamic, B, x_seidel, n);

    for (int i = 0; i < n; i++) {
        delete[] A_dynamic[i];
    }
    delete[] A_dynamic;

    return 0;
}