#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bstnode_t
{
    int key;
    struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t
{
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode *create_node(int value)
{
    BSTNode *newNode = malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *insert(BSTNode *root, int value)
{
    if (root == NULL)
        return create_node(value);

    if (value < root->key)
        root->left = insert(root->left, value);
    else if (value > root->key)
        root->right = insert(root->right, value);

    return root;
}

BSTNode *searchPreOrder(BSTNode *root, int value)
{
    if (root == NULL)
        return NULL;
    if (root->key == value)
        return root;
    BSTNode *left = searchPreOrder(root->left, value);
    if (left)
        return left;
    return searchPreOrder(root->right, value);
}

BSTNode *searchInOrder(BSTNode *root, int value)
{
    if (root == NULL)
        return NULL;
    BSTNode *left = searchInOrder(root->left, value);
    if (left)
        return left;
    if (root->key == value)
        return root;
    return searchInOrder(root->right, value);
}

BSTNode *searchPostOrder(BSTNode *root, int value)
{
    if (root == NULL)
        return NULL;
    BSTNode *left = searchPostOrder(root->left, value);
    if (left)
        return left;
    BSTNode *right = searchPostOrder(root->right, value);
    if (right)
        return right;
    if (root->key == value)
        return root;
    return NULL;
}

void bst_init(BST *bst)
{
    bst->_root = NULL;
    bst->_size = 0;
}

void bst_insert(BST *bst, int value)
{
    bst->_root = insert(bst->_root, value);
    bst->_size++;
}

bool bst_find_preorder(BST *bst, int value)
{
    return searchPreOrder(bst->_root, value) != NULL;
}
bool bst_find_inorder(BST *bst, int value)
{
    return searchInOrder(bst->_root, value) != NULL;
}
bool bst_find_postorder(BST *bst, int value)
{
    return searchPostOrder(bst->_root, value) != NULL;
}

void print_inorder(BSTNode *root)
{
    if (!root)
        return;
    print_inorder(root->left);
    printf("%d ", root->key);
    print_inorder(root->right);
}

int main()
{
    BST tree;
    bst_init(&tree);
    int input, data;
    printf("How many data you want to add: ");
    scanf("%d", &input);

    printf("Enter the data:\n");
    while (input--)
    {
        scanf("%d", &data);
        bst_insert(&tree, data);
    }

    int target;
    printf("Enter data you want to find: ");
    scanf("%d", &target);

    printf("InOrder: ");
    print_inorder(tree._root);
    printf("\n");

    printf("Find %d (PreOrder): %s\n", target, bst_find_preorder(&tree, target) ? "Found" : "Not Found");
    printf("Find %d (InOrder): %s\n", target, bst_find_inorder(&tree, target) ? "Found" : "Not Found");
    printf("Find %d (PostOrder): %s\n", target, bst_find_postorder(&tree, target) ? "Found" : "Not Found");
}
