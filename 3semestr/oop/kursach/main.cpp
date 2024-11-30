#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>  // Для использования kbhit() и getch()

using namespace std;

struct Record {
    int id;
    string name;
    int age;
    string city;
    double salary;
};

vector<Record> records = {
    {1, "Alice", 30, "New York", 50000.0},
    {2, "Bob", 25, "Los Angeles", 45000.0},
    {3, "Charlie", 35, "Chicago", 55000.0},
    {4, "David", 40, "Miami", 60000.0},
    {5, "Eve", 29, "Dallas", 52000.0},
    {6, "Frank", 33, "Boston", 48000.0},
    {7, "Grace", 28, "Houston", 53000.0},
    {8, "Heidi", 36, "Phoenix", 51000.0},
    {9, "Ivan", 32, "San Francisco", 59000.0},
    {10, "Judy", 27, "Seattle", 47000.0},
    {11, "Karl", 30, "Denver", 55000.0},
    {12, "Liam", 26, "Portland", 46000.0},
    {13, "Mia", 34, "Austin", 54000.0},
    {14, "Nathan", 29, "San Diego", 52000.0},
    {15, "Olivia", 38, "Las Vegas", 59000.0},
    {16, "Paul", 31, "Dallas", 51000.0},
    {17, "Quinn", 39, "New York", 60000.0},
    {18, "Rita", 25, "Miami", 45000.0},
    {19, "Sam", 34, "Chicago", 55000.0},
    {20, "Tom", 32, "Los Angeles", 52000.0}
};

int currentPage = 0;
int rowsPerPage = 20;
int currentColumn = 0;

void displayTable(int startIndex) {
    system("cls"); // Очистка экрана

    // Заголовки столбцов
    cout << " ID  | Name      | Age | City         | Salary" << endl;
    cout << "-------------------------------------------------" << endl;

    for (int i = startIndex; i < startIndex + rowsPerPage && i < records.size(); ++i) {
        cout << records[i].id << " | "
             << records[i].name << " | "
             << records[i].age << " | "
             << records[i].city << " | "
             << records[i].salary << endl;
    }

    cout << "\nUse arrow keys for navigation, PgUp/PgDn for page navigation, "
         << "1-5 to sort by column, F to search by ID.\n";
}

void sortRecords(int column) {
    switch (column) {
        case 0:
            sort(records.begin(), records.end(), [](const Record &a, const Record &b) { return a.id < b.id; });
            break;
        case 1:
            sort(records.begin(), records.end(), [](const Record &a, const Record &b) { return a.name < b.name; });
            break;
        case 2:
            sort(records.begin(), records.end(), [](const Record &a, const Record &b) { return a.age < b.age; });
            break;
        case 3:
            sort(records.begin(), records.end(), [](const Record &a, const Record &b) { return a.city < b.city; });
            break;
        case 4:
            sort(records.begin(), records.end(), [](const Record &a, const Record &b) { return a.salary < b.salary; });
            break;
        default:
            break;
    }
}

void searchRecord() {
    int searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;

    bool found = false;
    for (const auto& record : records) {
        if (record.id == searchId) {
            cout << "Record found: " << record.id << " | "
                 << record.name << " | "
                 << record.age << " | "
                 << record.city << " | "
                 << record.salary << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Record not found!" << endl;
    }
}

void navigate() {
    char ch;
    while (true) {
        displayTable(currentPage * rowsPerPage);
        ch = _getch(); // Ожидаем ввода с клавиатуры

        if (ch == 27) { // Если нажата клавиша ESC, завершаем программу
            break;
        }

        switch (ch) {
            case 224: // Блок для обработки стрелочных клавиш
                ch = _getch();
                if (ch == 72) { // Стрелка вверх
                    if (currentPage > 0) {
                        --currentPage;
                    }
                } else if (ch == 80) { // Стрелка вниз
                    if ((currentPage + 1) * rowsPerPage < records.size()) {
                        ++currentPage;
                    }
                }
                break;
            case 73: // PgUp
                if (currentPage > 0) --currentPage;
                break;
            case 81: // PgDn
                if ((currentPage + 1) * rowsPerPage < records.size()) ++currentPage;
                break;
            case 71: // Home
                currentPage = 0;
                break;
            case 79: // End
                currentPage = records.size() / rowsPerPage;
                break;
            case '1': case '2': case '3': case '4': case '5':
                currentColumn = ch - '1'; // Выбор столбца для сортировки
                sortRecords(currentColumn);
                break;
            case 'f': case 'F':
                searchRecord();
                break;
            default:
                break;
        }
    }
}

int main() {
    navigate();
    return 0;
}
