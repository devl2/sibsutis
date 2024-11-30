#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

struct NaselennyPunkt {
    char FIO[32];
    char street[18];
    short int houseNumber;
    short int apartmentNumber;
    char Date[10];
};

struct Node {
    NaselennyPunkt Data;
    Node* next;
    int id;
};

struct Ochered {
    Node* head;
    Node* tail;
    int id = 1; 
};

struct tree {
    NaselennyPunkt Data;
    int id;
    int weight;
    bool use;
    int index;
    tree* L = nullptr;
    tree* R = nullptr;
};

int getYear(const char* date) {
    int year;
    sscanf_s(date + 6, "%d", &year);
    return year;
}

int getMonth(const char* date) {
    int month;
    sscanf_s(date + 3, "%d", &month);
    return month;
}

int getDay(const char* date) {
    int day;
    sscanf_s(date, "%d", &day);
    return day;
}

int compareNaselennyPunkt(const NaselennyPunkt& a, const NaselennyPunkt& b) {
    int yearA = getYear(a.Date), yearB = getYear(b.Date);
    if (yearA != yearB) return yearA - yearB;

    int monthA = getMonth(a.Date), monthB = getMonth(b.Date);
    if (monthA != monthB) return monthA - monthB;

    int dayA = getDay(a.Date), dayB = getDay(b.Date);
    if (dayA != dayB) return dayA - dayB;

    return strcmp(a.street, b.street);
}

void HeapBuild(NaselennyPunkt* arr[], int L, int R) {
    NaselennyPunkt* x = arr[L];
    int i = L;

    while (true) {
        int j = 2 * i + 1;
        if (j > R) {
            break;
        }

        if (j < R && compareNaselennyPunkt(*arr[j + 1], *arr[j]) > 0) {
            j++;
        }

        if (compareNaselennyPunkt(*x, *arr[j]) >= 0) {
            break;
        }

        arr[i] = arr[j];
        i = j;
    }
    arr[i] = x;
}

void HeapSort(NaselennyPunkt* arr[], int n) {
    NaselennyPunkt* temp;
    int L = n / 2 - 1;

    while (L >= 0) {
        HeapBuild(arr, L, n - 1);
        L--;
    }

    int R = n - 1;
    while (R > 0) {
        temp = arr[0];
        arr[0] = arr[R];
        arr[R] = temp;
        R--;
        HeapBuild(arr, 0, R);
    }
}

NaselennyPunkt** loadData(const char* Base, int& count) {
    FILE* file;
    errno_t err = fopen_s(&file, Base, "rb");

    if (err != 0) {
        cerr << "File opening error: " << Base << endl;
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    count = fileSize / sizeof(NaselennyPunkt);

    NaselennyPunkt** indexArray = new NaselennyPunkt * [count];

    for (int i = 0; i < count; ++i) {
        indexArray[i] = new NaselennyPunkt;
        fread(indexArray[i], sizeof(NaselennyPunkt), 1, file);
    }

    fclose(file);
    return indexArray;
}

void print20Records(NaselennyPunkt* arr[], int count) {
    const int recordsPerPage = 20;
    for (int i = 0; i < count; i++) {
        cout << setw(5) << i + 1 << " | " << arr[i]->FIO << " | "
            << arr[i]->street << " | "
            << arr[i]->houseNumber << " | "
            << setw(3) << arr[i]->apartmentNumber << " | "
            << arr[i]->Date << " |" << endl;

        if ((i + 1) % recordsPerPage == 0) {
            char response;
            bool validInput = false;

            do {
                cout << "Should I show 20 more entries? (y/n): ";
                cin >> response;

                if (response == 'y' || response == 'Y') {
                    validInput = true;
                }
                else if (response == 'n' || response == 'N') {
                    return;
                }
                else {
                    cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                }
            } while (!validInput);
        }
    }

    cout << "All records have been displayed. Press any key to return to the menu...";
    cin.ignore();
    cin.get();
}

void addToQueue(Ochered* queue, NaselennyPunkt& item) {
    Node* newNode = new Node();
    newNode->Data = item;
    newNode->next = nullptr;
    newNode->id = queue->id++;

    if (queue->tail == nullptr) {
        queue->head = newNode;
        queue->tail = newNode;
    }
    else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

void printQueue(Ochered* queue) {
    Node* current = queue->head;
    while (current != nullptr) {
        cout << setw(5) << current->id << " | " // Используем id из узла
            << current->Data.FIO << " | "
            << current->Data.street << " | "
            << current->Data.houseNumber << " | "
            << setw(3) << current->Data.apartmentNumber << " | "
            << current->Data.Date << "|" << endl;
        current = current->next;
    }

}

int binarySearch(NaselennyPunkt** arr, int count, int targetYear) {
    int left = 0, right = count - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int year = getYear(arr[mid]->Date);

        if (year == targetYear) {
            result = mid;
            right = mid - 1;
        }
        else if (year < targetYear) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

void insert(tree*& root, tree* node, int& treeID) {
    if (root == nullptr) {
        root = new tree{ node->Data, treeID++, node->weight, node->use, node->index };
    }
    else if (node->weight > root->weight) {
        insert(root->L, node, treeID);
    }
    else {
        insert(root->R, node, treeID);
    }
}


void Obhod(tree* root) {
    if (root) {
        Obhod(root->L); 
        cout << setw(5) << root->id << " | "
            << root->Data.FIO << " | "
            << root->Data.street << " | "
            << root->Data.houseNumber << " | "
            << setw(3) << root->Data.apartmentNumber << " | "
            << root->Data.Date << "| "
            << setw(4) << root->weight << " |" << endl;
        Obhod(root->R); 
    }
}

void algorithmA1(tree nodes[], int n, tree*& rootA1) {
    rootA1 = nullptr;
    int treeID = 1;

    for (int i = 0; i < n; ++i) {
        int maxWeight = 0;
        int index = -1;

        for (int j = 0; j < n; ++j) {
            if (!nodes[j].use && nodes[j].weight >= maxWeight) {
                maxWeight = nodes[j].weight;
                index = j;
            }
        }

        if (index != -1) {
            nodes[index].use = true;
            insert(rootA1, &nodes[index], treeID);
        }
    }
}


void searchByApartment(tree* root, int apartmentNumber) {
    if (root == nullptr) return;

    // Ищем в левом поддереве
    searchByApartment(root->L, apartmentNumber);

    // Проверка текущего узла
    if (root->Data.apartmentNumber == apartmentNumber) {
        cout << setw(5) << root->id << " | "
            << root->Data.FIO << " | "
            << root->Data.street << " | "
            << root->Data.houseNumber << " | "
            << setw(3) << root->Data.apartmentNumber << " | "
            << root->Data.Date << "| "
            << setw(4) << root->weight << " |" << endl;
    }

    // Ищем в правом поддереве
    searchByApartment(root->R, apartmentNumber);
}

void RabotaSDerevom(Ochered* queue) {
    int n = 0;
    Node* current = queue->head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }
    // Инициализация массива узлов дерева с динамическим размером
    tree* nodes = new tree[n];
    current = queue->head;
    int index = 0;

    while (current != nullptr) {
        nodes[index].Data = current->Data;
        nodes[index].weight = rand() % 10000;
        nodes[index].use = false;
        index++;

        current = current->next;
    }

    tree* rootA1 = nullptr;
    algorithmA1(nodes, n, rootA1);

    cout << endl << endl;
    cout << "Tree traversal (A1): " << endl;

    Obhod(rootA1);
    cout << endl;

    char apartmentNumber[10];
    int apart;
    bool validInput = false;

    do {
        cout << "Enter apartment number to search or N to exit : ";
        cin >> apartmentNumber;

        if (strcmp(apartmentNumber, "N") == 0 || strcmp(apartmentNumber, "n") == 0) {
            validInput = true;
            break;
        }
        apart = atoi(apartmentNumber);
        if (apart > 0) {
            searchByApartment(rootA1, apart);
            validInput = true;
        }
        else {
            cout << "Invalid year apartment number";
        }
    } while (!validInput);

    delete[] nodes;
}

void searchRecordsByYear(NaselennyPunkt** arr, int count, int targetYear) {
    Ochered* queue = new Ochered();
    queue->head = nullptr;
    queue->tail = nullptr;

    int index = binarySearch(arr, count, targetYear);
    if (index == -1) {
        cout << "Records with the year of settlement " << targetYear << " have not been found." << endl;
        return;
    }

    addToQueue(queue, *arr[index]);

    int i = index - 1;
    while (i >= 0 && getYear(arr[i]->Date) == targetYear) {
        addToQueue(queue, *arr[i]);
        i--;
    }

    i = index + 1;
    while (i < count && getYear(arr[i]->Date) == targetYear) {
        addToQueue(queue, *arr[i]);
        i++;
    }

    printQueue(queue);

    char input[10];
    bool validInput = false;

    do {
        cout << endl;
        cout << "Enter T to create a tree or N to exit: ";
        cin >> input;

        if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
            validInput = true;
            break;
        }

        if (strcmp(input, "T") == 0 || strcmp(input, "t") == 0) {
            RabotaSDerevom(queue);
            validInput = true;
        }
        else {
            cout << "Incorrect input. Please enter T to create a tree or N to exit:" << endl;
        }
    } while (!validInput);

    Node* temp;
    while (queue->head != nullptr) {
        temp = queue->head;
        queue->head = queue->head->next;
        delete temp;
    }
    delete queue;
    cout << "Press any key to return to the menu...";
    cin.ignore();
    cin.get();
}

void printAllRecords(NaselennyPunkt* arr[], int count) {
    for (int i = 0; i < count; i++) {
        cout << setw(5) << i + 1 << " | " << arr[i]->FIO << " | "
            << arr[i]->street << "| "
            << arr[i]->houseNumber << " | "
            << setw(3) << arr[i]->apartmentNumber << " | "
            << arr[i]->Date << "|" << endl;
    }
}

NaselennyPunkt** createCopy(NaselennyPunkt** original, int count) {
    NaselennyPunkt** copy = new NaselennyPunkt * [count];
    for (int i = 0; i < count; ++i) {
        copy[i] = new NaselennyPunkt(*original[i]);
    }
    return copy;
}

int main() {
    SetConsoleCP(866);
    SetConsoleOutputCP(866);

    int count = 0;
    char choice;
    bool exit = false;

    NaselennyPunkt** arr = loadData("D:/solutions/kurs(ne robit)/testBase4.dat", count);

    if (arr == nullptr) {
        return -1;
    }

    NaselennyPunkt** originalArr = createCopy(arr, count);

    do {
        SetConsoleCP(866);
        SetConsoleOutputCP(866);

        cout << "1. Output an unordered list" << endl;
        cout << "2. Output a sorted list" << endl;
        cout << "3. Output 20 sorted records each" << endl;
        cout << "4. Exit" << endl;
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
        case '1':
            printAllRecords(originalArr, count);
            cout << "Press any key to return to the menu...";
            cin.ignore();
            cin.get();
            break;
        case '2': {
            HeapSort(arr, count);
            printAllRecords(arr, count);

            char input[10];
            bool validInput = false;
            int targetYear = 0;

            do {
                cout << endl;
                cout << "Enter the year to search (for example, 96 for 1996) or enter N to exit: ";
                cin >> input;

                if (strcmp(input, "N") == 0 || strcmp(input, "n") == 0) {
                    validInput = true;
                    break;
                }

                targetYear = atoi(input);

                if (targetYear >= 93 && targetYear <= 97) {
                    validInput = true;
                    searchRecordsByYear(arr, count, targetYear);
                }
                else {
                    cout << "Invalid year. Please enter a valid year (e.g., 96 for 1996 or 1996)." << endl;
                }
            } while (!validInput);

            break;
        }

        case '3':
            HeapSort(arr, count);
            print20Records(arr, count);
            break;
        case '4':
            exit = true;
            break;
        default:
            SetConsoleCP(866);
            SetConsoleOutputCP(866);
            cout << "Invalid choice" << endl;
            cout << "Press any key to return to the menu...";
            cin.ignore();
            cin.get();
        }

    } while (!exit);

    for (int i = 0; i < count; ++i) {
        delete arr[i];
        delete originalArr[i];
    }
    delete[] arr;
    delete[] originalArr;

    return 0;
}

