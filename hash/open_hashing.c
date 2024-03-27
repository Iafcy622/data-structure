#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MIN_TABLE_SIZE 11

typedef struct _ListNode
{
    int key;
    struct _ListNode *next;
} ListNode;

typedef struct _HashTable
{
    int size;
    ListNode **lists;
} HashTable;

int NextPrime(int N);
HashTable *createHashTable();
int hash(int value, int size);
ListNode *find(HashTable *m, int value);
void insert(HashTable *m, int value);
void delete(HashTable *m, int value);
void freeTable(HashTable *m);

static int nextPrime(int N)
{
    int i;

    if (N % 2 == 0)
        N++;
    for (;; N += 2)
    {
        for (i = 3; i * i <= N; i += 2)
            if (N % i == 0)
                goto ContOuter;
        return N;
    ContOuter:;
    }
}

HashTable *createHashTable(int size)
{
    HashTable *m = (HashTable *)malloc(sizeof(HashTable));

    if (m == NULL)
        return NULL;

    if (size < MIN_TABLE_SIZE)
        m->size = MIN_TABLE_SIZE;
    else
        m->size = nextPrime(size);

    m->lists = malloc(sizeof(ListNode) * m->size);

    for (int i = 0; i < m->size; i++)
    {
        m->lists[i] = (ListNode *)malloc(sizeof(ListNode));

        if (m->lists[i] == NULL)
            return NULL;
        else
            m->lists[i]->next = NULL;
    }

    return m;
}

int hash(int value, int size)
{
    return value % size;
}

ListNode *find(HashTable *m, int value)
{
    ListNode *head = m->lists[hash(value, m->size)];
    ListNode *temp = head->next;

    while (temp != NULL && temp->key != value)
        temp = temp->next;

    return temp;
}

void insert(HashTable *m, int value)
{
    ListNode *temp = find(m, value);

    if (temp == NULL)
    {
        ListNode *node = (ListNode *)malloc(sizeof(ListNode));

        if (node == NULL)
            return;

        node->key = value;
        ListNode *head = m->lists[hash(value, m->size)];
        node->next = head->next;
        head->next = node;
    }
}

void delete(HashTable *m, int value)
{
    ListNode *temp1 = m->lists[hash(value, m->size)];

    while (temp1->next != NULL && temp1->next->key != value)
        temp1 = temp1->next;

    if (temp1 != NULL && temp1->next != NULL && temp1->next->key == value)
    {
        ListNode *temp2 = temp1->next;
        temp1->next = temp2->next;
        free(temp2);
    }
}

void freeTable(HashTable *m)
{
    for (int i = 0; i < m->size; i++)
    {
        ListNode *node = m->lists[i];
        ListNode *temp;

        while (node != NULL)
        {
            temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(m);
}

void printHash(HashTable *m)
{
    for (int i = 0; i < m->size; i++)
    {
        printf("%d: ", i);
        ListNode *n = m->lists[i];
        while (n->next != NULL)
        {
            n = n->next;
            printf("%d ", n->key);
        }
        printf("\n");
    }
}

int main()
{
    HashTable *m1 = createHashTable(8);
    printf("Size: %d\n", m1->size);
    insert(m1, 2);
    insert(m1, 4);
    insert(m1, 13);
    insert(m1, 24);
    printHash(m1);
    printf("2? : %s\n", find(m1, 2) ? "Yes" : "No");
    delete (m1, 2);
    delete (m1, 1);
    printHash(m1);
    printf("2? : %s\n", find(m1, 2) ? "Yes" : "No");
    freeTable(m1);

    return 0;
}