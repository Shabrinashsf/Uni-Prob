#include <stdio.h>
#include <stdlib.h>
// acc
typedef struct
{
    int value;
    int baris;
    int kolom;
} ELEMENT;

int compare(const void *a, const void *b)
{
    ELEMENT *elemA = (ELEMENT *)a;
    ELEMENT *elemB = (ELEMENT *)b;
    return (elemA->value - elemB->value);
}

int binser(ELEMENT arr[], int xy, int target)
{
    int start = 0;
    int end = xy - 1;
    while (start <= end)
    {
        int elemen = (start + end) / 2;
        if (arr[elemen].value == target)
        {
            return elemen;
        }
        if (target > arr[elemen].value)
        {
            start = elemen + 1;
        }
        else
        {
            end = elemen - 1;
        }
    }
    return -1;
}

int main()
{
    int x, y, target, index = 0;
    scanf("%d %d", &x, &y);
    ELEMENT matrix[x * y];
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int temp;
            scanf("%d", &temp);
            matrix[index].value = temp;
            matrix[index].baris = i + 1;
            matrix[index].kolom = j + 1;
            index++;
        }
    }
    scanf("%d", &target);

    qsort(matrix, x * y, sizeof(ELEMENT), compare);

    int find = binser(matrix, x * y, target);
    if (find != -1)
    {
        printf("Element %d found at position: (%d, %d).", matrix[find].value, matrix[find].baris, matrix[find].kolom);
    }
    else
    {
        printf("Element %d not found.", target);
    }
}
