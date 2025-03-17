#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

double function(double x) {
    return pow(x, 2) - 3;
}

double proizv(double x) {
    return 2 * x;
}

double Interval(double a, double b) {
    if (function(a) == 0) return a;
    if (function(b) == 0) return b;
    return -1;
}

int main() {
    srand(time(NULL));
    double a = 1;
    double b = 2;
    const int size = 2; 
    double epsilon = 1e-8;
    double interval[size] = {a, b};

    cout << fixed << setprecision(10);

    cout << "\nPolov Method" << endl;
    double prevC = 0;
    int step = 0;
    while (true) {
        step++;
        cout << "Step " << step << endl;
        double c = (interval[0] + interval[1]) / 2;
        double IntervalCheck = function(interval[0]) * function(c);
        if (IntervalCheck < 0) {
            interval[1] = c;
        } else {
            IntervalCheck = function(c) * function(interval[1]);
            if (IntervalCheck < 0) {
                interval[0] = c;
            }
        }
        cout << "Interval: (";
        for (int j = 0; j < size; j++) {
            cout << " " << interval[j];
        }
        cout << " )" << endl;

        if (fabs(c - prevC) < epsilon) {break;}
        prevC = c;
    }

    cout << "\nHord Method" << endl;
    interval[0] = a;
    interval[1] = b;
    step = 0;
    prevC = 0;
    while (true) {
        step++;
        cout << "Step " << step << endl;
        double newC = (interval[0] * function(interval[1]) - interval[1] * function(interval[0])) / (function(interval[1]) - function(interval[0]));
        double IntervalCheck = function(interval[0]) * function(newC);
        if (IntervalCheck < 0) {
            interval[1] = newC;
        } else {
            IntervalCheck = function(newC) * function(interval[1]);
            if (IntervalCheck < 0) {
                interval[0] = newC;
            }
        }
        cout << "Interval: (";
        for (int j = 0; j < size; j++) {
            cout << " " << interval[j];
        }
        cout << " )" << endl;

        if (fabs(newC - prevC) < epsilon) {break;}
        prevC = newC;
    }

    cout << "\nNewton's Method" << endl;
    interval[0] = a;
    interval[1] = b;
    double root = Interval(a, b);
    step = 0;
    prevC = 0;
    while (true) {
        step++;
        cout << "Step " << step << endl;
        double newRoot = root - (function(root) / proizv(root));
        cout << "x" << step << " = " << newRoot << endl;

        if (fabs(newRoot - prevC) < epsilon) {break;}
        prevC = newRoot;
        root = newRoot;
    }

    return 0;
}