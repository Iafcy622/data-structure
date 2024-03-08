#include <stdio.h>
#include <stdlib.h>

struct Heap
{
    int *arr;
    int size;
    int capacity;
};

typedef struct Heap heap;

heap *createHeap(int capacity, int *nums);
void insertHelper(heap *h, int index);
void heapify(heap *h, int index);
int extractMin(heap *h);
void insert(heap *h, int data);

heap *createHeap(int capacity, int *nums) // O(n)
{
    heap *h = (heap *)malloc(sizeof(heap));

    if (h == NULL)
    {
        printf("Memory error");
        return NULL;
    }

    h->size = 0;
    h->capacity = capacity;

    h->arr = (int *)malloc(capacity * sizeof(int));

    if (h->arr == NULL)
    {
        printf("Memory error");
        return NULL;
    }

    int i;
    for (i = 0; i < capacity; i++)
        h->arr[i] = nums[i];

    h->size = i;
    i = (h->size - 2) / 2; // parent of last element
    while (i >= 0)
        heapify(h, i--);

    return h;
}

// helper to maintain minHeap property
void insertHelper(heap *h, int index)
{
    int parent = (index - 1) / 2;

    if (h->arr[parent] > h->arr[index])
    {
        // swap arr[parent] and arr[index]
        int temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;

        // recursively check the above level
        insertHelper(h, parent);
    }
}

void heapify(heap *h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    left = (left >= h->size || left < 0) ? -1 : left;
    right = (right >= h->size || right < 0) ? -1 : right;

    // set min to the index of the min between arr[left], arr[right], arr[index]
    if (left != -1 && h->arr[left] < h->arr[index])
        min = left;
    if (right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if (min != index)
    {
        // swap arr[min], arr[index]
        int temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;

        // recursively check the lower level
        heapify(h, min);
    }
}

int extractMin(heap *h)
{
    int min;

    // empty heap
    if (h->size == 0)
        return -999;

    min = h->arr[0];

    // swap root with last element
    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    heapify(h, 0);
    return min;
}

void insert(heap *h, int data)
{
    if (h->size < h->capacity)
    {
        h->arr[h->size] = data;
        insertHelper(h, h->size);
        h->size++;
    }
}

void printHeap(heap *h)
{

    for (int i = 0; i < h->size; i++)
    {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(int);
    heap *hp = createHeap(n, arr);

    printHeap(hp);
    extractMin(hp);
    printHeap(hp);

    return 0;
}
