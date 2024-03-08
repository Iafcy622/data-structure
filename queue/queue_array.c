#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Queue
{
    int *arr;
    int capacity;
    int front;
    int rear;
    int size;
} Queue;

Queue *createQueue(int capacity);
void freeQueue(Queue *q);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);
void clear(Queue *q);

Queue *createQueue(int capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->arr = (int *)malloc(sizeof(int) * capacity);
    q->capacity = capacity;
    clear(q);
    return q;
}

void freeQueue(Queue *q)
{
    if (q != NULL)
    {
        free(q->arr);
        free(q);
    }
}

bool isEmpty(Queue *q)
{
    return q->size == 0;
}

bool isFull(Queue *q)
{
    return q->size == q->capacity;
}

void enqueue(Queue *q, int data)
{
    q->size++;
    q->arr[q->rear++] = data;
}

int dequeue(Queue *q)
{
    if (isEmpty(q)) return 0;

    int data = q->arr[q->front];
    q->size--;
    q->front++;
    return data;
}

void clear(Queue *q)
{
    q->size = 0;
    q->front = 0;
    q->rear = 0;
}

void printQueue(Queue *q)
{
    if(isEmpty(q)) return;

    int i = q->front;
    while(i != q->rear)
    {
        printf("%d ", q->arr[i++]);
    }

    printf("\n");
}

int main()
{
    Queue *q = createQueue(5);

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);

    printQueue(q);

    return 0;
}