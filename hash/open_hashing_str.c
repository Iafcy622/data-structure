#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MIN_TABLE_SIZE 11

typedef struct _ListNode
{
    char *key;
    struct _ListNode *next;
} ListNode;

typedef struct _HashTable
{
    int size;
    ListNode **lists;
} HashTable;

int NextPrime(int N);
HashTable *createHashTable();
int hash(char *key, int size);
ListNode *find(HashTable *m, char *key);
void insert(HashTable *m, char *key);
void delete(HashTable *m, char *key);
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

int hash(char *key, int size)
{
    unsigned int hashVal = 0;

    while (*key != '\0')
        hashVal = (hashVal << 5) + *key++;

    return hashVal % size;
}

ListNode *find(HashTable *m, char *key)
{
    ListNode *head = m->lists[hash(key, m->size)];
    ListNode *temp = head->next;

    while (temp != NULL && strcmp(temp->key, key) != 0)
        temp = temp->next;

    return temp;
}

void insert(HashTable *m, char *key)
{
    ListNode *temp = find(m, key);

    if (temp == NULL)
    {
        ListNode *node = (ListNode *)malloc(sizeof(ListNode));

        if (node == NULL)
            return;

        node->key = malloc(sizeof(key));
        strcpy(node->key, key);
        ListNode *head = m->lists[hash(key, m->size)];
        node->next = head->next;
        head->next = node;
    }
}

void delete(HashTable *m, char *key)
{
    ListNode *temp1 = m->lists[hash(key, m->size)];

    while (temp1->next != NULL && strcmp(temp1->next->key, key) != 0)
        temp1 = temp1->next;

    if (temp1 != NULL && temp1->next != NULL && strcmp(temp1->next->key, key) == 0)
    {
        ListNode *temp2 = temp1->next;
        temp1->next = temp2->next;
        free(temp2->key);
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
            free(temp->key);
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
            printf("\"%s\" ", n->key);
        }
        printf("\n");
    }
}

int main()
{
    HashTable *m1 = createHashTable(8);
    printf("Size: %d\n", m1->size);

    insert(m1, "Hello");
    insert(m1, "IT9");
    insert(m1, "On99");
    insert(m1, "Test");
    insert(m1, "Test");
    insert(m1, "tes");
    printHash(m1);

    printf("Hello? %s\n", find(m1, "Hello") ? "Yes" : "No");
    delete (m1, "Hello");
    delete (m1, "On99");
    printHash(m1);
    printf("Hello? %s\n", find(m1, "Hello") ? "Yes" : "No");

    freeTable(m1);

    return 0;
}