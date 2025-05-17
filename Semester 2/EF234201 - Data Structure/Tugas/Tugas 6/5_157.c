#include <stdio.h>
#include <stdlib.h>

typedef struct bstnode_t
{
    int data;
    struct bstnode_t *left, *right;
} BST;

BST *createNode(int value)
{
    BST *newNode = (BST *)malloc(sizeof(BST));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BST *insert(BST *root, int value)
{
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

BST *findMin(BST *node)
{
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

BST *findMax(BST *node)
{
    while (node && node->right != NULL)
        node = node->right;
    return node;
}

BST *delete_specific(BST *root, int key)
{
    if (root == NULL)
        return NULL;

    if (key < root->data)
        root->left = delete_specific(root->left, key);
    else if (key > root->data)
        root->right = delete_specific(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            BST *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BST *temp = root->left;
            free(root);
            return temp;
        }
        BST *temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete_specific(root->right, temp->data);
    }
    return root;
}

BST *delete_replacesuccessor(BST *root)
{
    if (root == NULL)
        return NULL;

    if (root->right)
    {
        BST *successor = findMin(root->right);
        root->data = successor->data;
        root->right = delete_specific(root->right, successor->data);
    }
    else
    {
        BST *temp = root->left;
        free(root);
        return temp;
    }
    return root;
}

BST *delete_replacepredecessor(BST *root)
{
    if (root == NULL)
        return NULL;

    if (root->left)
    {
        BST *predecessor = findMax(root->left);
        root->data = predecessor->data;
        root->left = delete_specific(root->left, predecessor->data);
    }
    else
    {
        BST *temp = root->right;
        free(root);
        return temp;
    }
    return root;
}

void inorderTraversal(BST *root)
{
    if (root)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main()
{
    BST *root = NULL;
    int N, data;

    printf("How many data you want to add? : ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("\n");
    printf("Original BST by in-order: ");
    inorderTraversal(root);
    printf("\n");

    if (root != NULL)
    {
        printf("Root: %d\n", root->data);

        if (root->right != NULL)
        {
            BST *successor = findMin(root->right);
            printf("\n");
            printf("Successor of root: %d\n", successor->data);
            printf("BST after replacment root with successor (in-order):\n");
            root = delete_replacesuccessor(root);
            inorderTraversal(root);
            printf("\nRoot: %d\n", root->data);
        }
        else
        {
            printf("\nNo successor found\n");
        }

        if (root->left != NULL)
        {
            BST *predecessor = findMax(root->left);
            printf("\n");
            printf("Predecessor of root: %d\n", predecessor->data);
            printf("BST after replacment root with predecessor (in-order):\n");
            root = delete_replacepredecessor(root);
            inorderTraversal(root);
            printf("\nRoot: %d\n", root->data);
        }
        else
        {
            printf("\nNo predecessor found\n");
        }
    }

    return 0;
}
