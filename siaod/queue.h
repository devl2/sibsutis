#pragma once

typedef struct queue;
queue* initQueue();
bool empty(queue* start, queue* end);
void push(queue** start, queue** end, int data);
int dequeue(queue** start, queue** end);
void fillInc(queue** start, queue** end, int start, int end);
void fillDec(queue** start, queue** end, int start, int end);
void fillRand(queue** start, queue** end, int count, int min, int max);

