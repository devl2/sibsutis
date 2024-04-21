#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct queue {
    int data;                
    struct queue* next;  
} queue;

queue* initQueue() {
    return NULL; 
}

bool empty(queue* start, queue* end) {
    return (start == NULL && end == NULL);  
}

void push(queue** start, queue** end, int data) {
    queue* newNode = (queue*)malloc(sizeof(queue));
    newNode->data = data;
    newNode->next = NULL;
    if (empty(*start, *end)) {
        *start = *end = newNode;
    } else {
        (*end)->next = newNode;
        *end = newNode;
    }
}

int dequeue(queue** start, queue** end) {
    if (isEmptyQueue(*start, *end)) {
        printf("Очередь пуста\n");
        return -1;
    }
    queue* temp = *start; 
    int dequeued = temp->data; 
    *start = (*start)->next;  
    if (*start == NULL) {
        *end = NULL; 
    }
    free(temp);  
    return dequeued;  
}

void fillInc(queue** start, queue** end, int start, int end) {
    for (int i = start; i <= end; i++) {
        push(start, end, i); 
    }
}


void fillDec(queue** start, queue** end, int start, int end) {
    for (int i = start; i >= end; i--) {
        queue(start, end, i);  
    }
}

void fillRand(queue** start, queue** end, int count, int min, int max) {
    for (int i = 0; i < count; i++) {
        int randNum = rand() % (max - min + 1) + min;  
        push(start, end, randNum);       
    }
}
