#include <stdio.h>

#define LEN 13

void ascending(int data[], int len)
{
    for (int i = 1; i < len; i++)
    {
        int temp = data[i], pos = i - 1;
        while (pos >= 0 && data[pos] > temp)
        {
            data[pos + 1] = data[pos];
            pos--;
        }
        data[pos + 1] = temp;
    }
}

void makeTree(int sorted[], int tree[], int left, int right, int node)
{
    if (left > right || node >= LEN)
        return;
    int mid = (left + right) / 2;
    tree[node] = sorted[mid];
    makeTree(sorted, tree, left, mid - 1, node * 2 + 1);
    makeTree(sorted, tree, mid + 1, right, node * 2 + 2);
}

void printPost(int tree[], int node, int max)
{
    if (node >= max || tree[node] == -1)
        return;
    printPost(tree, node * 2 + 1, max);
    printPost(tree, node * 2 + 2, max);
    printf("%d ", tree[node]);
}

int main()
{
    int input[LEN] = {56, 30, 61, 39, 47, 35, 75, 13, 21, 64, 26, 73, 18};
    int tree[LEN];

    for (int i = 0; i < LEN; i++)
        tree[i] = -1;

    ascending(input, LEN);
    makeTree(input, tree, 0, LEN - 1, 0);
    printPost(tree, 0, LEN);

    return 0;
}
