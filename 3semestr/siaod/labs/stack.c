#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct StackNode {
    int data;               
    struct StackNode* next; 
} StackNode;

StackNode* initStack() {
    return NULL;  
}

bool isEmpty(StackNode* root) {
    return !root; 
}

void push(StackNode** root, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = *root;
    *root = newNode;
}

int pop(StackNode** root) {
    if (isEmpty(*root)) {
        printf("Стек пуст\n"); 
        return -1;
    }
    StackNode* temp = *root; 
    *root = (*root)->next;   
    int popped = temp->data;  
    free(temp);             
    return popped;            
}

void fillStackInc(StackNode** root, int start, int end) {
    for (int i = start; i <= end; i++) {
        push(root, i); 
    }
}

void fillStackDec(StackNode** root, int start, int end) {
    for (int i = start; i >= end; i--) {
        push(root, i); 
    }
}

void fillStackRand(StackNode** root, int count, int min, int max) {
    for (int i = 0; i < count; i++) {
        int randNumber = rand() % max + 1;
        push(root, randNumber);                          
    }
}

typedef struct QueueNode {
    int data;                
    struct QueueNode* next;  
} QueueNode;

QueueNode* initQueue() {
    return NULL;  
}

bool isEmptyQueue(QueueNode* front, QueueNode* rear) {
    return (front == NULL && rear == NULL);  
}

void add_queue(QueueNode** front, QueueNode** rear, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmptyQueue(*front, *rear)) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

int del_queue(QueueNode** front, QueueNode** rear) {
    if (isEmptyQueue(*front, *rear)) {
        printf("Очередь пуста\n");  
        return -1;
    }
    QueueNode* temp = *front;  
    int dequeued = temp->data;
    *front = (*front)->next;   
    if (*front == NULL) {
        *rear = NULL;  
    }
    free(temp);  
    return dequeued;  
}

void fillQueueInc(QueueNode** front, QueueNode** rear, int start, int end) {
    for (int i = start; i <= end; i++) {
        add_queue(front, rear, i);  
    }
}

void fillQueueDec(QueueNode** front, QueueNode** rear, int start, int end) {
    for (int i = start; i >= end; i--) {
        add_queue(front, rear, i);  
    }
}

void fillQueueRand(QueueNode** front, QueueNode** rear, int count, int min, int max) {
    for (int i = 0; i < count; i++) {
        int randomNumber = rand() % (max - min + 1) + min;  
        add_queue(front, rear, randomNumber);             
    }
}

typedef struct ListNode {
    int data;              
    struct ListNode* next;  
} ListNode;

void appendToList(ListNode** head, int data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        ListNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; 
        }
        temp->next = newNode;
    }
}

void printList(ListNode* head) {
    ListNode* temp = head;
    printf("Элементы списка: ");
    while (temp != NULL) {
        printf("%d ", temp->data); 
        temp = temp->next;
    }
    printf("\n");
}

int checksum(ListNode* head) {
    int sum = 0;
    ListNode* temp = head;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->next;
    }
    return sum;
}

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
            count++; 
        }
        temp = next;  
    }
    return count;
}


int main() {
    srand(time(NULL));
    StackNode* stack = initStack();
    fillStackInc(&stack, 1, 20);
    printf("Элементы стека (возрастающие числа): ");
    while (!isEmpty(stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    /*
    printf("\n");
    fillStackDec(&stack, 20, 1);
    printf("Элементы стека (убывающие числа): ");
    while (!isEmpty(stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    printf("\n");
    fillStackRand(&stack, 3, 1, 20);
    printf("Элементы стека (рандомные числа): ");
    while (!isEmpty(stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
    
    */
    QueueNode* queueFront = NULL;
    QueueNode* queueRear = NULL;

    printf("---------------------------------------------------------");

    printf("\n");
    
    fillQueueInc(&queueFront, &queueRear, 1, 20);
    printf("Элементы очереди (возрастающие числа): ");
    while (!isEmptyQueue(queueFront, queueRear)) {
        printf("%d ", del_queue(&queueFront, &queueRear));
    }
    printf("\n");

    /*printf("\n");
    fillQueueDec(&queueFront, &queueRear, 20, 1);
    printf("Элементы очереди (убывающие числа): ");
    while (!isEmptyQueue(queueFront, queueRear)) {
        printf("%d ", del_queue(&queueFront, &queueRear));
    }
    printf("\n");

    printf("\n");
    fillStackRand(&stack, 3, 1, 20);
    printf("Элементы стека (рандомные числа): ");
    while (!isEmpty(stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
    */

    ListNode* list = NULL;
    appendToList(&list, 10);
    appendToList(&list, 20);
    appendToList(&list, 20);
    appendToList(&list, 30);
    appendToList(&list, 40);
    appendToList(&list, 40);
    appendToList(&list, 40);
    appendToList(&list, 50);
    appendToList(&list, 50);

    printf("----------------------------------------------------");

    printf("\n");
    printList(list);
    printf("\n");
    printf("Контрольная сумма: %d\n", checksum(list));
    printf("Количество серий: %d\n", countSeries(list));

    return 0;
}