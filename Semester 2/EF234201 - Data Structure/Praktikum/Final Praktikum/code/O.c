#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t
{
    long long key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t
{
    BSTNode *_root;
    unsigned int _size;
} BST;

long long pre[100005];
long long z = 0;

BSTNode *__bst__createNode(long long value)
{
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *__bst__insert(BSTNode *root, long long value)
{
    if (root == NULL)
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);

    return root;
}

BSTNode *__bst__search(BSTNode *root, long long value)
{
    while (root != NULL)
    {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

void __bst__preorder(BSTNode *root)
{
    if (root)
    {
        pre[z++] = root->key;
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

void bst_init(BST *bst)
{
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_find(BST *bst, long long value)
{
    BSTNode *temp = __bst__search(bst->_root, value);
    return temp != NULL && temp->key == value;
}

void bst_insert(BST *bst, long long value)
{
    if (!bst_find(bst, value))
    {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_preorder(BST *bst)
{
    z = 0;
    __bst__preorder(bst->_root);
}

int main()
{
    BST set;
    bst_init(&set);

    int t;
    scanf("%d", &t);
    long long input[100005];

    for (int i = 0; i < t; i++)
    {
        scanf("%lld", &input[i]);
        bst_insert(&set, input[i]);
    }

    bst_preorder(&set);

    int same = 1;
    for (int i = 0; i < t; i++)
    {
        if (input[i] != pre[i])
        {
            same = 0;
            break;
        }
    }

    if (same)
        printf("Ini pohon\n");
    else
        printf("Ini bukan pohon\n");

    return 0;
}
