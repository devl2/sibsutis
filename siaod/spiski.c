#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура для элемента стека
typedef struct StackNode {
    int data;               // Данные элемента стека
    struct StackNode* next; // Указатель на следующий элемент стека
} StackNode;

// Инициализация пустого стека
StackNode* initStack() {
    return NULL;  // Возвращаем NULL, так как стек пуст
}

// Проверка, пуст ли стек
bool isEmpty(StackNode* root) {
    return !root;  // Возвращаем true, если root равен NULL (стек пуст)
}

// Добавление элемента в стек
void push(StackNode** root, int data) {
    // Выделяем память под новый элемент стека
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    // Устанавливаем данные нового элемента
    newNode->data = data;
    // Новый элемент указывает на текущую вершину стека
    newNode->next = *root;
    // Обновляем указатель на вершину стека, теперь он указывает на новый элемент
    *root = newNode;
}

// Удаление элемента из стека
int pop(StackNode** root) {
    if (isEmpty(*root)) {
        printf("Стек пуст\n");  // Выводим сообщение об ошибке, если стек пуст
        return -1;
    }
    StackNode* temp = *root;  // Временный указатель на вершину стека
    *root = (*root)->next;     // Перемещаем указатель на вершину на следующий элемент
    int popped = temp->data;   // Получаем данные из удаляемого элемента
    free(temp);                // Освобождаем память, выделенную для удаляемого элемента
    return popped;             // Возвращаем данные удаленного элемента
}

// Функция для заполнения стека возрастающими числами
void fillIncreasing(StackNode** root, int start, int end) {
    for (int i = start; i <= end; i++) {
        push(root, i);  // Добавляем числа в стек
    }
}

// Функция для заполнения стека убывающими числами
void fillDecreasing(StackNode** root, int start, int end) {
    for (int i = start; i >= end; i--) {
        push(root, i);  // Добавляем числа в стек
    }
}

// Функция для заполнения стека случайными числами
void fillRandom(StackNode** root, int count, int min, int max) {
    for (int i = 0; i < count; i++) {
        int randomNumber = rand() % (max - min + 1) + min;  // Генерируем случайное число в заданном диапазоне
        push(root, randomNumber);                           // Добавляем случайное число в стек
    }
}

// Структура для элемента очереди
typedef struct QueueNode {
    int data;                // Данные элемента очереди
    struct QueueNode* next;  // Указатель на следующий элемент очереди
} QueueNode;

// Инициализация пустой очереди
QueueNode* initQueue() {
    return NULL;  // Возвращаем NULL, так как очередь пуста
}

// Проверка, пуста ли очередь
bool isEmptyQueue(QueueNode* front, QueueNode* rear) {
    return (front == NULL && rear == NULL);  // Возвращаем true, если front и rear равны NULL (очередь пуста)
}

// Добавление элемента в очередь
void enqueue(QueueNode** front, QueueNode** rear, int data) {
    // Выделяем память под новый элемент очереди
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    // Устанавливаем данные нового элемента
    newNode->data = data;
    newNode->next = NULL;
    // Если очередь пуста, новый элемент становится ее началом
    if (isEmptyQueue(*front, *rear)) {
        *front = *rear = newNode;
    } else {
        // Иначе новый элемент добавляется в конец очереди
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

// Удаление элемента из очереди
int dequeue(QueueNode** front, QueueNode** rear) {
    if (isEmptyQueue(*front, *rear)) {
        printf("Очередь пуста\n");  // Выводим сообщение об ошибке, если очередь пуста
        return -1;
    }
    QueueNode* temp = *front;  // Временный указатель на начало очереди
    int dequeued = temp->data; // Получаем данные из удаляемого элемента
    *front = (*front)->next;   // Перемещаем указатель на начало на следующий элемент
    if (*front == NULL) {
        *rear = NULL;  // Если удаленный элемент был последним, то указатель на конец становится NULL
    }
    free(temp);  // Освобождаем память, выделенную для удаляемого элемента
    return dequeued;  // Возвращаем данные удаленного элемента
}

// Функция для заполнения очереди возрастающими числами
void fillQueueIncreasing(QueueNode** front, QueueNode** rear, int start, int end) {
    for (int i = start; i <= end; i++) {
        enqueue(front, rear, i);  // Добавляем числа в очередь
    }
}

// Функция для заполнения очереди убывающими числами
void fillQueueDecreasing(QueueNode** front, QueueNode** rear, int start, int end) {
    for (int i = start; i >= end; i--) {
        enqueue(front, rear, i);  // Добавляем числа в очередь
    }
}

// Функция для заполнения очереди случайными числами
void fillQueueRandom(QueueNode** front, QueueNode** rear, int count, int min, int max) {
    for (int i = 0; i < count; i++) {
        int randomNumber = rand() % (max - min + 1) + min;  // Генерируем случайное число в заданном диапазоне
        enqueue(front, rear, randomNumber);                 // Добавляем случайное число в очередь
    }
}

// Структура для элемента связанного списка
typedef struct ListNode {
    int data;               // Данные элемента списка
    struct ListNode* next;  // Указатель на следующий элемент списка
} ListNode;

// Функция для добавления элемента в конец списка
void appendToList(ListNode** head, int data) {
    // Выделяем память под новый элемент списка
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;  // Если список пуст, новый элемент становится его началом
    } else {
        ListNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;  // Перемещаемся в конец списка
        }
        temp->next = newNode;  // Добавляем новый элемент в конец списка
    }
}

// Функция для печати элементов списка
void printList(ListNode* head) {
    ListNode* temp = head;
    printf("Элементы списка: ");
    while (temp != NULL) {
        printf("%d ", temp->data);  // Выводим данные текущего элемента
        temp = temp->next;
    }
    printf("\n");
}

// Функция для подсчета контрольной суммы элементов списка
int checksum(ListNode* head) {
    int sum = 0;
    ListNode* temp = head;
    while (temp != NULL) {
        sum += temp->data;  // Суммируем данные элементов списка
        temp = temp->next;
    }
    return sum;
}

// Функция для подсчета количества серий в списке
int countSeries(ListNode* head) {
    int count = 0;
    ListNode* temp = head;
    while (temp != NULL) {
        ListNode* current = temp;
        ListNode* next = temp->next;
        while (next != NULL && current->data == next->data) {
            next = next->next;
        }
        if (next != NULL) {
            count++;  // Увеличиваем счетчик серий, если найдена серия
        }
        temp = next;  // Переходим к следующему элементу после серии
    }
    return count;
}
