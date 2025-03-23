#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

double func1(double x, double y) {
    return pow(x, 2) + pow(y, 3) - 4;
}

double func2(double x, double y) {
    return x / y - 2;
}

double prozv(double (*f)(double, double), double x, double y, double h, int varIndex) {
    if (varIndex == 0) {
        return (f(x + h, y) - f(x - h, y)) / (2 * h);
    } else {
        return (f(x, y + h) - f(x, y - h)) / (2 * h);
    }
}

int main() {
    const int x_size = 2;
    double x = 2, y = 1;
    double x_mas[x_size] = {x, y};
    double h = 1e-5;
    double epsilon = 1e-6;
    int step = 0;

    cout << "Matrix" << endl;

    while (true) {
        step++;
        double F[x_size] = {func1(x_mas[0], x_mas[1]), func2(x_mas[0], x_mas[1])};
        
        double W[x_size][x_size] = {
            {prozv(func1, x_mas[0], x_mas[1], h, 0), prozv(func1, x_mas[0], x_mas[1], h, 1)},
            {prozv(func2, x_mas[0], x_mas[1], h, 0), prozv(func2, x_mas[0], x_mas[1], h, 1)}
        };

        double WT[x_size][x_size] = {W[1][1], -W[0][1], -W[1][0], W[0][0]};
        double W_1[x_size][x_size];
        double del1 = 1, del2 = 1, delW;

        cout << "Шаг: " << step << endl;

        cout << "F(x" << step << ")" << endl;
        for (int i = 0; i < x_size; i++) {
            cout << F[i] << endl;
        }

        for (int i = x_size - 1; i >= 0; i--) {
            del1 *= W[i][i];
            for (int j = x_size - 1; j >= i + 1; j--) {
                del2 *= W[i][j];
            }
        }
        delW = del1 - del2;

        cout << "W: " << endl;
        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < x_size; j++) {
                cout << " " << W[i][j];
            }
            cout << endl;
        }
        cout << endl;

        cout << "WT: " << endl;
        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < x_size; j++) {
                cout << " " << WT[i][j];
            }
            cout << endl;
        }
		cout << endl;

        cout << "W^-1:" << endl;
        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < x_size; j++) {
                W_1[i][j] = 1 / delW * WT[i][j];
                cout << " " << W_1[i][j];
            }
            cout << endl;
        }
		cout << endl;

        cout << "X" << step << ": " << endl;
        double stek[x_size];

        for (int i = 0; i < x_size; i++) {
            double row = 0;
            for (int j = 0; j < x_size; j++) {
                row += W_1[i][j] * F[j];
            }
            stek[i] = x_mas[i] - row;
        }

        double diff_x = abs(stek[0] - x_mas[0]);
        double diff_y = abs(stek[1] - x_mas[1]);

        x_mas[0] = stek[0];
        x_mas[1] = stek[1];

        for (int i = 0; i < x_size; i++) {
            cout << "x" << i + 1 << "=" << x_mas[i] << endl;
        }
        cout << endl << endl;

        if (diff_x < epsilon && diff_y < epsilon) {
            cout << "Точность достигнута на шаге " << step << endl;
            break;
        }
    }

    return 0;
}