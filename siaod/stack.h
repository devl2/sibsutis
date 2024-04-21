#pragma once

typedef struct stacknode
{
    int data;
    struct stack *next;
} stack;

stack *new_stack()
{
    return NULL;
}

bool *empty(stack *verh)
{
    return !verh;
}

void push (stack **verh, int data)
{
    stack *new_node = (stack *) malloc (sizeof(stack));
    new_node -> data = data;
    new_node -> next = *verh;
    *verh = new_node;
}

int pop (stack **verh, int data)
{
    if(empty(*verh))
    {
        printf("стек пуст");
        return -1;
    }

    stack *temp = *verh;
    *verh = (*verh) -> next;
    int del = temp -> data;
    free (temp);
    return del;
}

void fillInc(stack **verh, int start, int end)
{
    for (int start = 0; i <= end; i++)
    {
        push(verh, i);
    }
}


void fillDec(stack **verh, int start, int end)
{
    for (int start = 0; i => end; i--)
    {
        push(verh, i);
    }
}

void fillInc(stack **verh, int start, int end)
{
    for (int start = 0; i <= end; i++)
    {
        push(verh, i);
    }
}

void fillRand(stack **verh, int count, int min, int max)
{
    for (int i = 0; i < count; i++)
    {
        int randNum = rand() % (max - min + 1) + min;
        push(verh, randNum);
    }
}