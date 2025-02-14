#include <iostream>
#include <cstring>
#include <algorithm> // для работы с функциями строки, такими как strncmp

using namespace std;

// Функция бинарного поиска по первым трем символам названия улицы
int binarySearchByPrefix(char streets[][50], int size, const char* prefix) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Сравниваем первые три символа строки посередине с заданным префиксом
        if (strncmp(streets[mid], prefix, 3) == 0) {
            return mid; // Возвращаем индекс найденного элемента
        } else if (strncmp(streets[mid], prefix, 3) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Если элемент не найден
}

int main() {
    // Массив строк с улицами (каждая строка может быть до 50 символов)
    char streets[][50] = {
        "Abbey Road", "Baker Street", "Canal Street", "Dover Road", "Elm Street", "First Avenue", "Grove Street"
    };
    int size = sizeof(streets) / sizeof(streets[0]);

    // Сортируем массив улиц лексикографически
    std::sort(streets, streets + size, [](const char* a, const char* b) {
        return strcmp(a, b) < 0;
    });

    char prefix[4];
    cout << "Введите первые три буквы названия улицы для поиска: ";
    cin >> prefix;

    int result = binarySearchByPrefix(streets, size, prefix);

    if (result != -1) {
        cout << "Улица найдена: " << streets[result] << endl;
    } else {
        cout << "Улица с таким префиксом не найдена." << endl;
    }

    return 0;
}
