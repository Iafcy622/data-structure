#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Stack
{
    int *arr;
    int capacity;
    int top;
} Stack;

Stack *createStack(int capacity);
void freeStack(Stack *s);
void push(Stack *s, int x);
int pop(Stack *s);
void clear(Stack *s);
bool isEmpty(Stack *s);
bool isFull(Stack *s);
int top(Stack *s);
int size(Stack *s);

Stack *createStack(int capacity)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->capacity = capacity;
    s->arr = (int *)malloc(sizeof(int) * capacity);
    clear(s);
    return s;
}

void freeStack(Stack *s)
{
    if (s != NULL)
    {
        free(s->arr);
        free(s);
    }
}

void push(Stack *s, int x)
{
    if (isFull(s))
        return;
    s->arr[++s->top] = x;
}

int pop(Stack *s)
{
    if (isEmpty(s))
        return 0;
    return s->arr[s->top--];
}

void clear(Stack *s)
{
    s->top = -1;
}

bool isEmpty(Stack *s)
{
    return s->top == -1;
}

bool isFull(Stack *s)
{
    return s->top == s->capacity - 1;
}

int top(Stack *s)
{
    if (isEmpty(s))
        return -1;

    return s->arr[s->top];
}

int size(Stack *s)
{
    return s->top + 1;
}

int main()
{
    int n = 5;
    Stack *s = createStack(n);

    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);

    printf("Size: %d\n", size(s));

    int i = 0;
    while(!isEmpty(s))
    {
        printf("%d-th element: %d\n", i++, top(s));
        pop(s);
    }

    freeStack(s);

    return 0;
}