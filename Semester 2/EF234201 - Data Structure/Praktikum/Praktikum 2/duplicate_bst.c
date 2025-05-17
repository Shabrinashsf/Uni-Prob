#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t
{
    long long key;
    int kemunculan;
    struct bstnode_t
        *left,
        *right;
} BSTNode;

typedef struct bst_t
{
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode *__bst__createNode(long long value)
{
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->kemunculan = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *__bst__insert(BSTNode *node, long long value)
{
    if (node == NULL)
    {
        BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
        newNode->key = value;
        newNode->kemunculan = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (value < node->key)
        node->left = __bst__insert(node->left, value);
    else if (value > node->key)
        node->right = __bst__insert(node->right, value);
    else
        node->kemunculan++;

    return node;
}

BSTNode *__bst__insert__kemunculan(BSTNode *root, long long value)
{
    if (root->key == value)
    {
        root->kemunculan += 1;
        return root;
    }

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

BSTNode *__bst__findMinNode(BSTNode *node)
{
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;

    return currNode;
}

BSTNode *__bst__remove(BSTNode *root, long long value, int *node_deleted)
{
    if (root == NULL)
        return NULL;

    if (value > root->key)
        root->right = __bst__remove(root->right, value, node_deleted);
    else if (value < root->key)
        root->left = __bst__remove(root->left, value, node_deleted);
    else
    {

        if (root->kemunculan > 1)
        {
            root->kemunculan--;
            *node_deleted = 0;
            return root;
        }

        *node_deleted = 1;

        if (root->left == NULL)
        {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }

        else if (root->right == NULL)
        {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key = temp->key;
        root->kemunculan = temp->kemunculan;
        temp->kemunculan = 1;
        root->right = __bst__remove(root->right, temp->key, node_deleted);
    }
    return root;
}

void __bst__inorder(BSTNode *root)
{
    if (root)
    {
        __bst__inorder(root->left);
        printf("%lld(%d) ", root->key, root->kemunculan);
        __bst__inorder(root->right);
    }
}

void __bst__postorder(BSTNode *root)
{
    if (root)
    {
        __bst__postorder(root->left);
        __bst__postorder(root->right);
        printf("%lld(%d) ", root->key, root->kemunculan);
    }
}

void __bst__preorder(BSTNode *root)
{
    if (root)
    {
        printf("%lld(%d) ", root->key, root->kemunculan);
        __bst__preorder(root->left);
        __bst__preorder(root->right);
    }
}

void bst_init(BST *bst)
{
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst)
{
    return bst->_root == NULL;
}

bool bst_find(BST *bst, long long value)
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;

    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, long long value)
{
    bst->_root = __bst__insert(bst->_root, value);
    bst->_size++;
}

void bst_remove(BST *bst, long long value)
{
    int node_deleted = 0;
    if (bst_find(bst, value))
    {
        bst->_root = __bst__remove(bst->_root, value, &node_deleted);
        if (node_deleted)
            bst->_size--;
    }
}

void bst_inorder(BST *bst)
{
    __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst)
{
    __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst)
{
    __bst__preorder(bst->_root);
}

int main()
{
    BST set;
    bst_init(&set);
    int n;
    char cmd[10];
    long long in, del;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "insert") == 0)
        {
            getchar();
            scanf("%lld", &in);
            bst_insert(&set, in);
        }
        else if (strcmp(cmd, "remove") == 0)
        {
            getchar();
            scanf("%lld", &del);
            bst_remove(&set, del);
        }
        else if (strcmp(cmd, "inorder") == 0)
        {
            bst_inorder(&set);
            printf("\n");
        }
        else if (strcmp(cmd, "preorder") == 0)
        {
            bst_preorder(&set);
            printf("\n");
        }
        else if (strcmp(cmd, "postorder") == 0)
        {
            bst_postorder(&set);
            printf("\n");
        }
    }

    return 0;
}

/*
input
16
insert 12
insert 12
insert 12
insert 10
insert 10
insert 9
insert 11
insert 20
inorder
preorder
postorder
remove 9
remove 10
inorder
preorder
postorder

output
9(1) 10(2) 11(1) 12(3) 20(1)
12(3) 10(2) 9(1) 11(1) 20(1)
9(1) 11(1) 10(2) 20(1) 12(3)
10(1) 11(1) 12(3) 20(1)
12(3) 10(1) 11(1) 20(1)
11(1) 10(1) 20(1) 12(3)
*/