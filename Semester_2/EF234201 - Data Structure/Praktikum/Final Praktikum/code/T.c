#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left, *right;
    int height;
} AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
} AVL;

AVLNode *_avl_createNode(int value)
{
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode *_search(AVLNode *root, int value)
{
    while (root != NULL)
    {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
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

    printf("Left Case\n");
    printf("PivotNode: %d\n", pivotNode->data);
    if (pivotNode->left)
        printf("PivotNode->left: %d\n", pivotNode->left->data);
    if (pivotNode->left && pivotNode->left->left)
        printf("PivotNode->left->left: %d\n", pivotNode->left->left->data);

    printf("\n");

    pivotNode->left = newParrent->right;
    newParrent->right = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    printf("result:\n");
    printf("NewNode: %d\n", newParrent->data);
    if (newParrent->left)
        printf("NewNode->left: %d\n", newParrent->left->data);
    if (newParrent->right)
        printf("NewNode->right: %d\n", newParrent->right->data);

    return newParrent;
}

AVLNode *_leftRotate(AVLNode *pivotNode)
{

    AVLNode *newParrent = pivotNode->right;

    printf("Right Case\n");
    printf("PivotNode: %d\n", pivotNode->data);
    if (pivotNode->right)
        printf("PivotNode->right: %d\n", pivotNode->right->data);
    if (pivotNode->right && pivotNode->right->right)
        printf("PivotNode->right->right: %d\n", pivotNode->right->right->data);

    printf("\n");

    pivotNode->right = newParrent->left;
    newParrent->left = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    printf("result:\n");
    printf("NewNode: %d\n", newParrent->data);
    if (newParrent->left)
        printf("NewNode->left: %d\n", newParrent->left->data);
    if (newParrent->right)
        printf("NewNode->right: %d\n", newParrent->right->data);

    return newParrent;
}

AVLNode *_otherRightRotate(AVLNode *pivotNode)
{

    AVLNode *newParrent = pivotNode->left;

    pivotNode->left = newParrent->right;
    newParrent->right = pivotNode;

    pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
    newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

    return newParrent;
}

AVLNode *_otherLeftRotate(AVLNode *pivotNode)
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
    printf("Left Right Case\n");
    printf("PivotNode: %d\n", node->data);
    if (node->left)
        printf("PivotNode->left: %d\n", node->left->data);
    if (node->left && node->left->right)
        printf("PivotNode->left->right: %d\n", node->left->right->data);

    printf("\n");

    node->left = _otherLeftRotate(node->left);
    AVLNode *res = _otherRightRotate(node);

    printf("result:\n");
    printf("NewNode: %d\n", res->data);
    if (res->left)
        printf("NewNode->left: %d\n", res->left->data);
    if (res->right)
        printf("NewNode->right: %d\n", res->right->data);

    return res;
}

AVLNode *_rightLeftCaseRotate(AVLNode *node)
{
    printf("Right Left Case\n");
    printf("PivotNode: %d\n", node->data);
    if (node->right)
        printf("PivotNode->right: %d\n", node->right->data);
    if (node->right && node->right->left)
        printf("PivotNode->right->left: %d\n", node->right->left->data);

    printf("\n");

    node->right = _otherRightRotate(node->right);
    AVLNode *res = _otherLeftRotate(node);

    printf("result:\n");
    printf("NewNode: %d\n", res->data);
    if (res->left)
        printf("NewNode->left: %d\n", res->left->data);
    if (res->right)
        printf("NewNode->right: %d\n", res->right->data);

    return res;
}

int _getBalanceFactor(AVLNode *node)
{
    if (node == NULL)
        return 0;
    return _getHeight(node->left) - _getHeight(node->right);
}

AVLNode *_insert_AVL(AVL *avl, AVLNode *node, int value)
{

    if (node == NULL)
        return _avl_createNode(value);
    if (value < node->data)
        node->left = _insert_AVL(avl, node->left, value);
    else if (value > node->data)
        node->right = _insert_AVL(avl, node->right, value);

    node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right));

    int balanceFactor = _getBalanceFactor(node);

    if (balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if (balanceFactor > 1 && value > node->left->data)
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

void avl_init(AVL *avl)
{
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl)
{
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, int value)
{
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;

    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl, int value)
{
    if (!avl_find(avl, value))
    {
        avl->_root = _insert_AVL(avl, avl->_root, value);
        avl->_size++;
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

int main()
{
    AVL avlku;
    avl_init(&avlku);
    int t;
    int x;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &x);
        avl_insert(&avlku, x);
    }
}

/*
Sample Input 0
3
10
20
30
Sample Output 0
Right Case
PivotNode: 10
PivotNode->right: 20
PivotNode->right->right: 30

result:
NewNode: 20
NewNode->left: 10
NewNode->right: 30


Sample Input 1
5
10
30
20
25
26

Sample Output 1
Right Left Case
PivotNode: 10
PivotNode->right: 30
PivotNode->right->left: 20

result:
NewNode: 20
NewNode->left: 10
NewNode->right: 30

Left Right Case
PivotNode: 30
PivotNode->left: 25
PivotNode->left->right: 26

result:
NewNode: 26
NewNode->left: 25
NewNode->right: 30
*/