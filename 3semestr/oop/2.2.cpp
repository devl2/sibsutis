#include <iostream>

int main() {
    int rows;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;

    int** mas = new int*[rows];
    int* elem = new int[rows];

    for (int i = 0; i < rows; ++i) {
        std::cout << "Введите количество элементов в строке " << i + 1 << ": ";
        std::cin >> elem[i];

        mas[i] = new int[elem[i]];

        for (int j = 0; j < elem[i]; ++j) {
            std::cout << "Введите элемент [" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> mas[i][j];
        }
    }

    std::cout << "Двумерный массив: \n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < elem[i]; ++j) {
            std::cout << mas[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < rows; ++i) {
        delete[] mas[i]; 
    }
    delete[] mas;
    delete[] elem;

    return 0;
}
