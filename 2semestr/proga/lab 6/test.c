#include <stdio.h>

// Функция для вычисления факториала
int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

// Функция для вычисления вероятности
void calculateProbability(int n, int m, float p, float *pd, float *pm) {
    // Проверка входных данных
    if (n < m || m < 0 || p < 0 || p > 1) {
        printf("Некорректные входные данные.\n");
        *pd = 0;
        *pm = 0;
        return;
    }

    // Вычисление коэффициента биномиального распределения
    float cnm = (float)factorial(n) / (factorial(m) * factorial(n - m));
    
    // Вычисление вероятности для m девочек
    *pd = cnm * pow(p, m) * pow(1 - p, n - m);

    // Вычисление вероятности для m мальчиков
    *pm = cnm * pow(1 - p, m) * pow(p, n - m);
}

int main() {
    int n, m;
    float p, pd, pm;

    printf("Введите количество детей (n): ");
    scanf("%d", &n);
    printf("Введите количество девочек (m): ");
    scanf("%d", &m);
    printf("Введите вероятность рождения девочки (p): ");
    scanf("%f", &p);

    calculateProbability(n, m, p, &pd, &pm);

    printf("Вероятность получить %d девочек: %.4f\n", m, pd);
    printf("Вероятность получить %d мальчиков: %.4f\n", m, pm);

    return 0;
}
