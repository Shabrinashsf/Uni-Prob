#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLNode_t
{
    long long data;
    struct AVLNode_t *left, *right;
    int height;
} AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
} AVL;

int print_bst[101];
int i = 0;

AVLNode *_avl_createNode(long long value)
{
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode *_search(AVLNode *root, long long value)
{
    while (root != NULL)
    {
        if (value < root->data)
        {
            root = root->left;
        }
        else if (value > root->data)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return root;
}

int _getHeight(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int _max(int a, int b)
{
    return (a > b) ? a : b;
}

AVLNode *_rightRotate(AVLNode *pivotNode)
{

    AVLNode *newParrent = pivotNode->left;
    pivotNode->left = newParrent->right;
    newParrent->right = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    return newParrent;
}

AVLNode *_leftRotate(AVLNode *pivotNode)
{

    AVLNode *newParrent = pivotNode->right;
    pivotNode->right = newParrent->left;
    newParrent->left = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    return newParrent;
}

AVLNode *_leftCaseRotate(AVLNode *node)
{
    return _rightRotate(node);
}

AVLNode *_rightCaseRotate(AVLNode *node)
{
    return _leftRotate(node);
}

AVLNode *_leftRightCaseRotate(AVLNode *node)
{
    node->left = _leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode *_rightLeftCaseRotate(AVLNode *node)
{
    node->right = _rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return _getHeight(node->left) - _getHeight(node->right);
}

AVLNode *_insert_AVL(AVL *avl, AVLNode *node, long long value)
{

    if (node == NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if (value < node->data)
        node->left = _insert_AVL(avl, node->left, value);
    else if (value > node->data)
        node->right = _insert_AVL(avl, node->right, value);

    node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));

    int balanceFactor = _getBalanceFactor(node);

    if (balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if (balanceFactor > 1 && value > node->left->data) //
        return _leftRightCaseRotate(node);
    if (balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if (balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);

    return node;
}

AVLNode *_findMinNode(AVLNode *node)
{
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode *_remove_AVL(AVLNode *node, long long value)
{
    if (node == NULL)
        return node;
    if (value > node->data)
        node->right = _remove_AVL(node->right, value);
    else if (value < node->data)
        node->left = _remove_AVL(node->left, value);
    else
    {
        AVLNode *temp;
        if ((node->left == NULL) || (node->right == NULL))
        {
            temp = NULL;
            if (node->left == NULL)
                temp = node->right;
            else if (node->right == NULL)
                temp = node->left;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;

            free(temp);
        }
        else
        {
            temp = _findMinNode(node->right);
            node->data = temp->data;
            node->right = _remove_AVL(node->right, temp->data);
        }
    }

    if (node == NULL)
        return node;

    node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1;

    int balanceFactor = _getBalanceFactor(node);

    if (balanceFactor > 1 && _getBalanceFactor(node->left) >= 0)
        return _leftCaseRotate(node);

    if (balanceFactor > 1 && _getBalanceFactor(node->left) < 0)
        return _leftRightCaseRotate(node);

    if (balanceFactor < -1 && _getBalanceFactor(node->right) <= 0)
        return _rightCaseRotate(node);

    if (balanceFactor < -1 && _getBalanceFactor(node->right) > 0)
        return _rightLeftCaseRotate(node);

    return node;
}

void avl_init(AVL *avl)
{
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl)
{
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, long long value)
{
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;

    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl, long long value)
{
    if (!avl_find(avl, value))
    {
        avl->_root = _insert_AVL(avl, avl->_root, value);
        avl->_size++;
    }
}

void avl_remove(AVL *avl, long long value)
{
    if (avl_find(avl, value))
    {
        avl->_root = _remove_AVL(avl->_root, value);
        avl->_size--;
        printf("%lld deleted\n", value);
    }
    else
    {
        printf("%lld is not found in the tree\n", value);
    }
}

void preorder(AVLNode *root)
{
    if (root)
    {
        preorder(root->left);
        printf("%d ", root->data);
        preorder(root->right);
    }
}

void printPath(AVLNode *root, long long value)
{
    while (root != NULL)
    {
        if (value < root->data)
        {
            printf("%d ", root->data);
            root = root->left;
        }
        else if (value > root->data)
        {
            printf("%d ", root->data);
            root = root->right;
        }
        else
        {
            // terakhir, print node-nya sendiri
            printf("%d\n", root->data);
            return;
        }
    }
}

int main()
{
    AVL avlku;
    avl_init(&avlku);
    char cmd[7];
    int n;
    long long temp;
    long long target;
    long long hapus;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", cmd);
        if (strcmp(cmd, "INSERT") == 0)
        {
            getchar();
            scanf("%lld", &temp);
            if (avl_find(&avlku, temp))
            {
                printf("%lld is already in the tree\n", temp);
            }
            else
            {
                avl_insert(&avlku, temp);
                printf("%lld inserted\n", temp);
            }
            // gak boleh nilainya double
        }
        else if (strcmp(cmd, "FIND") == 0)
        {
            getchar();
            scanf("%lld", &target);
            // i = 0;
            if (avl_find(&avlku, target))
            {
                printf("%lld found with path: ", target);
                printPath(avlku._root, target);
            }
            else
            {
                printf("%lld not found\n", target);
            }
        }
        else if (strcmp(cmd, "DELETE") == 0)
        {
            getchar();
            scanf("%lld", &hapus);
            avl_remove(&avlku, hapus);
        }
    }
}

/*
7
INSERT 6
INSERT 3
INSERT 9
INSERT 4
FIND 4
DELETE 6
FIND 6

6 inserted
3 inserted
9 inserted
4 inserted
4 found with path: 6 3 4
6 deleted
6 not found
*/