#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node *left;
    struct _Node *right;
    int height;
} Node;

typedef struct _AvlTree
{
    Node *root;
} AvlTree;

AvlTree *createTree();
int max(int a, int b);
int height(Node *node);
Node *newNode(int data);
Node *rightRotate(Node *node);
Node *leftRotate(Node *node);
int getBalance(Node *node);
Node *insertHelper(Node *root, int data);
void insert(AvlTree *t, int data);
void delete(AvlTree *t, int data);
Node *deleteHelper(Node *root, int data);
void freeTree(AvlTree *t);
void freeNode(Node *root);
void printInorder(Node *root);
void printPreorder(Node *root);
void printPostorder(Node *root);
Node *findMin(Node *root);
Node *findMax(Node *root);

AvlTree *createTree()
{
    AvlTree *t = (AvlTree *)malloc(sizeof(AvlTree));
    t->root = NULL;

    return t;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int height(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL)
    {
        node->data = data;
        node->left = node->right = NULL;
        node->height = 1;
    }
    return node;
}

Node *rightRotate(Node *node)
{
    Node *x = node->left;
    Node *y = x->right;

    // rotate
    x->right = node;
    node->left = y;

    // update height
    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *node)
{
    Node *x = node->right;
    Node *y = x->left;

    // rotate
    x->left = node;
    node->right = y;

    // update height
    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node *insertHelper(Node *root, int data)
{
    // BST insertion
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insertHelper(root->left, data);
    else if (data > root->data)
        root->right = insertHelper(root->right, data);

    // Update height
    root->height = max(height(root->left), height(root->right)) + 1;

    // Balancing
    int bf = getBalance(root);

    // LL (Left heavy)
    if (bf > 1 && data < root->left->data)
        return rightRotate(root);

    // RR (Right heavy)
    if (bf < -1 && data > root->right->data)
        return leftRotate(root);

    // LR
    if (bf > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left); // turned to LL
        return rightRotate(root);
    }

    // RL
    if (bf < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right); // turned to RR
        return leftRotate(root);
    }

    return root;
}

void insert(AvlTree *t, int data)
{
    t->root = insertHelper(t->root, data);
}

void delete(AvlTree *t, int data)
{
    t->root = deleteHelper(t->root, data);
}

Node *deleteHelper(Node *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteHelper(root->left, data);
    else if (data > root->data)
        root->right = deleteHelper(root->right, data);
    else // found
    {
        // with 0 or 1 child
        if (root->left == NULL || root->right == NULL)
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) // 0 children
            {
                temp = root;
                root = NULL;
            }
            else // 1 child
                *root = *temp;

            free(temp);
        }
        else // 2 children
        {
            Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteHelper(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = max(height(root->right), height(root->left)) + 1;

    int bf = getBalance(root);

    // LL (Left heavy)
    if (bf > 1 && data < root->left->data)
        return rightRotate(root);

    // RR (Right heavy)
    if (bf < -1 && data > root->right->data)
        return leftRotate(root);

    // LR
    if (bf > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left); // turned to LL
        return rightRotate(root);
    }

    // RL
    if (bf < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right); // turned to RR
        return leftRotate(root);
    }

    return root;
}

void freeNode(Node *node)
{
    if (node == NULL)
        return;
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

void freeTree(AvlTree *t)
{
    freeNode(t->root);
    free(t);
}

void printInorder(Node *root)
{
    if (root == NULL)
        return;

    // Left -> Root -> Right
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}

void printPreorder(Node *root)
{
    if (root == NULL)
        return;

    // Root → Left → Right
    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(Node *root)
{
    if (root == NULL)
        return;

    // Left → Right → Root
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->data);
}

Node *findMin(Node *root)
{
    // same as BST
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;
    return root;
}

Node *findMax(Node *root)
{
    // same as BST
    if (root == NULL)
        return NULL;

    while (root->right != NULL)
        root = root->right;

    return root;
}

int main()
{
    int arr[] = {3, 1, 4, 6, 9, 2, 8, 5, 7, 0};
    int n = sizeof(arr) / sizeof(int);

    AvlTree *t = createTree();

    for (int i = 0; i < n; i++)
        insert(t, arr[i]);

    //          3
    //      /      \
    //     1        6
    //   /  \     /   \
    //  0    2   4     8
    //            \   / \
    //             5  7  9
    printInorder(t->root);
    printf("\n");
    printPostorder(t->root);
    printf("\n");
    printPreorder(t->root);
    printf("\n");
    printf("Min: %d, Max: %d\n", findMin(t->root)->data, findMax(t->root)->data);

    //          3
    //      /      \
    //     1        6
    //   /  \     /   \
    //  0    2   4     9
    //            \   /
    //             5  7
    delete (t, 8);
    printInorder(t->root);
    printf("\n");
    printPostorder(t->root);
    printf("\n");
    printPreorder(t->root);
    printf("\n");

    freeTree(t);

    return 0;
}