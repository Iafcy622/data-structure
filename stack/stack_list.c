#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

typedef struct _Stack
{
    Node *top;
    int size;
} Stack;

Stack *createStack();
void freeStack(Stack *s);
void push(Stack *s, int data);
int pop(Stack *s);
void clear(Stack *s);
bool isEmpty(Stack *s);
int top(Stack *s);

Stack *createStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void freeStack(Stack *s)
{
    if (s != NULL)
    {
        clear(s);
        free(s);
    }
}

void push(Stack *s, int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    if (temp != NULL)
    {
        temp->data = data;
        temp->next = s->top;
        s->top = temp;
        s->size++;
    }
}

int pop(Stack *s)
{
    if(s == NULL)
        return 0;
    
    Node *temp;
    temp = s->top;
    s->top = s->top->next;

    int data = temp->data;
    free(temp);
    s->size--;

    return data;
}

void clear(Stack *s)
{
    if(s != NULL)
        while(!isEmpty(s))
            pop(s);
}

bool isEmpty(Stack *s)
{
    return s->top == NULL;
}

int top(Stack *s)
{
    if (isEmpty(s))
        return 0;

    return s->top->data;
}

int main()
{
    Stack *s = createStack();

    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);

    printf("Size: %d\n", s->size);

    int i = 0;
    while(!isEmpty(s))
    {
        printf("%d-th element: %d\n", i++, top(s));
        pop(s);
    }

    freeStack(s);

    return 0;
}