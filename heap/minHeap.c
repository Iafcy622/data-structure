#include <stdio.h>
#include <stdlib.h>

typedef struct _Heap
{
    int *arr;
    int size;
    int capacity;
} Heap;

Heap *createHeapLinear(int capacity, int *nums);
Heap *createHeap(int capacity);
void insertHelper(Heap *h, int index);
void minHeapify(Heap *h, int index);
int extractMin(Heap *h);
void insert(Heap *h, int data);
void freeHeap(Heap *h);

Heap *createHeapLinear(int capacity, int *nums) // O(n)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));

    if (h == NULL)
        return NULL;

    h->size = 0;
    h->capacity = capacity;

    h->arr = (int *)malloc(capacity * sizeof(int));

    if (h->arr == NULL)
        return NULL;

    int i;
    for (i = 0; i < capacity; i++)
        h->arr[i] = nums[i];

    h->size = i;
    i = (h->size - 2) / 2; // parent of last element
    while (i >= 0)
        minHeapify(h, i--);

    return h;
}

Heap *createHeap(int capacity)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));

    if (h == NULL)
        return NULL;

    h->size = 0;
    h->capacity = capacity;

    h->arr = (int *)malloc(capacity * sizeof(int));

    if (h->arr == NULL)
        return NULL;

    return h;
}

void insertHelper(Heap *h, int index)
{
    int parent = (index - 1) / 2;

    if (h->arr[parent] > h->arr[index])
    {
        int temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;

        insertHelper(h, parent);
    }
}

void minHeapify(Heap *h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    left = (left >= h->size || left < 0) ? -1 : left;
    right = (right >= h->size || right < 0) ? -1 : right;

    if (left != -1 && h->arr[left] < h->arr[index])
        min = left;
    if (right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if (min != index)
    {
        int temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;

        minHeapify(h, min);
    }
}

int extractMin(Heap *h)
{
    int min;

    if (h->size == 0)
        return -999;

    min = h->arr[0];

    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    minHeapify(h, 0);
    return min;
}

void insert(Heap *h, int data)
{
    if (h->size < h->capacity)
    {
        h->arr[h->size] = data;
        insertHelper(h, h->size);
        h->size++;
    }
}

void printHeap(Heap *h)
{

    for (int i = 0; i < h->size; i++)
        printf("%d ", h->arr[i]);

    printf("\n");
}

void freeHeap(Heap *h)
{
    if (h == NULL)
        return;
    free(h->arr);
    free(h);
}

int main()
{
    int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(int);
    Heap *hp = createHeap(n);

    for (int i = 0; i < n; i++)
    {
        insert(hp, arr[i]);
    }

    printHeap(hp);
    freeHeap(hp);

    return 0;
}
