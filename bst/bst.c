#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node
{
    int data;
    struct _Node *left;
    struct _Node *right;
} Node;

Node *newNode(int data);
Node *insert(Node *root, int data);
Node *delete(Node *root, int data);
Node *findMin(Node *root);
Node *findMax(Node *root);
bool find(Node *root, int k);
void freeTree(Node *root);
void printInorder(Node *root);
void printPreorder(Node *root);
void printPostorder(Node *root);

// standard operations

Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL)
    {
        node->data = data;
        node->left = node->right = NULL;
    }
    return node;
}

Node *insert(Node *root, int data)
{
    if (root == NULL) // create node
        return newNode(data);

    // recursively find the correct place to insert
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

Node *delete(Node *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
    {
        root->left = delete (root->left, data);
        return root;
    }
    else if (data > root->data)
    {
        root->left = delete (root->right, data);
        return root;
    }

    if (root->left == NULL)
        root = root->right;
    else if (root->right == NULL)
        root = root->left;
    else // have 2 children
    {
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete (root->right, root->data);
    }

    return root;
}

Node *findMin(Node *root)
{
    // recursive approach
    // if (root == NULL) return NULL;

    // if (root->left == NULL)
    //     return root;
    // else
    //     return findMin(root->left);

    // iterative approach
    if (root == NULL) return NULL;
    
    while(root->left != NULL)
        root = root->left;
    return root;
}

Node *findMax(Node *root)
{
    // iterative approach
    if (root == NULL) return NULL;

    while(root->right != NULL)
        root = root->right;

    return root;
}

bool find(Node *root, int k)
{
    // recursive approach
    // if(root == NULL) return false;

    // if(k < root->data)
    //     return find(root->left, k);
    // else if(k > root->data)
    //     return find(root->right, k);
    // else
    //     return true;

    // iterative approach
    while(root != NULL)
    {
        if(k > root->data)
            root = root->right;
        else if(k < root->data)
            root = root->left;
        else
            return true;
    }

    return false;
}

void freeTree(Node *root)
{
    if(root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// tree traversal

void printInorder(Node *root)
{
    if(root == NULL) return;

    // Left -> Root -> Right
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}

void printPreorder(Node *root)
{
    if(root == NULL) return;

    // Root → Left → Right
    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(Node *root)
{
    if(root == NULL) return;

    // Left → Right → Root
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->data);
}

int main()
{
    Node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);

    //        50
    //       /  \ 
    //     30   70
    //     /\   /
    //   20 40 60

    printf("Min: %d\n", findMin(root)->data);
    printf("Max: %d\n", findMax(root)->data);
    printf("80?: %s\n", find(root, 80) ? "Found" : "Not found");
    printf("60?: %s\n", find(root, 60) ? "Found" : "Not found");

    printf("Inorder: "); printInorder(root); printf("\n");
    printf("Preorder: "); printPreorder(root); printf("\n");
    printf("Postorder: "); printPostorder(root); printf("\n");

    freeTree(root);

    return 0;
}