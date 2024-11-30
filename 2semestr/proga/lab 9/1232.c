#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения информации о студенте
struct Student {
    char surname[50];
    int grades[4];
    struct Student* next;
};

// Функция для создания нового узла списка
struct Student* createNode(char* surname, int grades[]) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newNode->surname, surname);
    for (int i = 0; i < 4; ++i) {
        newNode->grades[i] = grades[i];
    }
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в конец списка
void append(struct Student** head, struct Student* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Функция для сортировки списка по фамилии
void sortList(struct Student** head) {
    struct Student *current, *nextStud;
    char temp[50];
    int tempGrades[4];

    if (*head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        nextStud = current->next;
        while (nextStud != NULL) {
            if (strcmp(current->surname, nextStud->surname) > 0) {
                strcpy(temp, current->surname);
                strcpy(current->surname, nextStud->surname);
                strcpy(nextStud->surname, temp);

                for (int i = 0; i < 4; ++i) {
                    tempGrades[i] = current->grades[i];
                    current->grades[i] = nextStud->grades[i];
                    nextStud->grades[i] = tempGrades[i];
                }
            }
            nextStud = nextStud->next;
        }
        current = current->next;
    }
}

// Функция для вывода списка
void printList(struct Student* head) {
    printf("Отсортированный список студентов:\n");
    while (head != NULL) {
        printf("Фамилия: %s, Оценки: %d %d %d %d\n",
               head->surname, head->grades[0], head->grades[1], head->grades[2], head->grades[3]);
        head = head->next;
    }
}

int main() {
    // Создание списка студентов
    struct Student* head = NULL;

    // Добавление элементов в список
    append(&head, createNode("Иванов", (int[]){4, 5, 3, 5}));
    append(&head, createNode("Петров", (int[]){3, 4, 5, 4}));
    append(&head, createNode("Сидоров", (int[]){5, 4, 4, 3}));

    // Сортировка списка
    sortList(&head);

    // Вывод списка
    printList(head);

    return 0;
}
