#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE (26)

typedef struct _TrieNode
{
    struct _TrieNode *children[ALPHABET_SIZE];
    bool isEndofWord;
} TrieNode;

typedef struct _Trie
{
    TrieNode *root;
} Trie;

TrieNode *newNode();
Trie *createTrie();
void insert(Trie *t, char *key);
bool find(Trie *t, char *key);
TrieNode *deleteHelper(TrieNode *root, char *key, int depth);
void *delete(Trie *t, char *key);
bool isEmpty(TrieNode *node);
void freeTrie(TrieNode *root);

TrieNode *newNode()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));

    if (node == NULL)
        return NULL;

    node->isEndofWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node;
}

Trie *createTrie()
{
    Trie *t = (Trie *)malloc(sizeof(Trie));
    TrieNode *root = newNode();

    if (t == NULL || root == NULL)
        return NULL;

    t->root = root;
}

void insert(Trie *t, char *key)
{
    TrieNode *temp = t->root;
    int n = strlen(key);

    for (int i = 0; i < n; i++)
    {
        int index = key[i] - 'a';

        if (!temp->children[index])
            temp->children[index] = newNode();

        temp = temp->children[index];
    }

    temp->isEndofWord = true;
}

bool find(Trie *t, char *key)
{
    TrieNode *temp = t->root;
    int n = strlen(key);

    for (int i = 0; i < n; i++)
    {
        int index = key[i] - 'a';

        if (!temp->children[index])
            return false;

        temp = temp->children[index];
    }

    return temp->isEndofWord;
}

void *delete(Trie *t, char *key)
{
    deleteHelper(t->root, key, 0);
}

TrieNode *deleteHelper(TrieNode *root, char *key, int depth)
{
    if (root == NULL)
        return NULL;

    if (depth == strlen(key))
    {
        if (root->isEndofWord)
            root->isEndofWord = false;

        if (isEmpty(root))
        {
            free(root);
            root = NULL;
        }

        return root;
    }

    int i = key[depth] - 'a';
    root->children[i] = deleteHelper(root->children[i], key, depth + 1);

    if (isEmpty(root) && !root->isEndofWord)
    {
        free(root);
        root = NULL;
    }

    return root;
}

bool isEmpty(TrieNode *node)
{
    if (node)
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (node->children[i])
                return false;

    return true;
}

void freeTrie(TrieNode *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(root->children[i]);

    free(root);
}

int main()
{
    char keys[8][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};

    Trie *t = createTrie();

    for (int i = 0; i < 8; i++)
        insert(t, keys[i]);

    printf("%s -> %s\n", "the", find(t, "the") ? "Found" : "Not found");
    printf("%s -> %s\n", "these", find(t, "these") ? "Found" : "Not found");

    printf("%s -> %s\n", "bye", find(t, "bye") ? "Found" : "Not found");
    delete (t, "bye");
    printf("%s -> %s\n", "bye", find(t, "bye") ? "Found" : "Not found");

    printf("%s -> %s\n", "answers", find(t, "answers") ? "Found" : "Not found");

    freeTrie(t->root);

    return 0;
}