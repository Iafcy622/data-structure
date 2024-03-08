#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

typedef struct _List
{
    Node *head;
    Node *tail;
    int n;
} List;

List *createList();
Node *newNode(int data);
void insert(List *l, int data);
void insertBehind(Node *node, int data);
void delete(List *l, int data);
Node *find(List *l, int data);
void freeList(List *l);
void printList(List *l);

List *createList()
{
    List *l = (List *)malloc(sizeof(List));

    if (l != NULL)
        l->n = 0;

    return l;
}

Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node != NULL)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

void insert(List *l, int data)
{
    Node *node = newNode(data);

    if (node == NULL)
        return;

    if (l->head == NULL)
        l->head = l->tail = node;
    else
    {
        l->tail->next = node;
        l->tail = node;
    }

    l->n++;
}

void insertBehind(Node *node, int data)
{
    if (node == NULL)
        return;

    Node *x = newNode(data);
    x->next = node->next;
    node->next = x;
}

void delete(List *l, int data)
{
    if (l == NULL)
        return;

    Node *prev = NULL;
    Node *curr = l->head;

    while (curr != NULL)
    {
        if (curr->data == data)
        {
            prev->next = curr->next;
            freeNode(curr);
            return;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

Node *find(List *l, int data)
{
    if (l == NULL)
        return NULL;

    Node *temp = l->head;

    while (temp != NULL)
    {
        if (temp->data == data)
            return temp;
        else
            temp = temp->next;
    }

    return NULL;
}

void freeList(List *l)
{
    Node *node = l->head;

    while (node != NULL)
    {
        Node *temp = node;
        node = node->next;
        free(temp);
    }

    free(l);
}

void printList(List *l)
{
    if (l == NULL)
        return;

    Node *node = l->head;
    while (node->next != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("%d\n", node->data);
}

int main()
{
    int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(int);

    List *l = createList();

    for (int i = 0; i < n; i++)
        insert(l, arr[i]);

    printList(l);

    delete (l, 7);
    printList(l);

    insertBehind(find(l, 4), 11);
    printList(l);

    printf("Have 3? %s\n", find(l, 3) == NULL ? "No" : "Yes");
    printf("Have 7? %s\n", find(l, 7) == NULL ? "No" : "Yes");

    freeList(l);

    return 0;
}