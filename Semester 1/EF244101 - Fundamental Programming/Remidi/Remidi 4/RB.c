#include <stdio.h>

void swapped(int arr2[], int n)
{
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr2[n - i - 1];
    }
    for (int i = 0; i < n; i++)
    {
        arr2[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        arr2[i] = temp[i];
    }
}

void numbersAddition(int arr1[], int arr2[], int n)
{
    swapped(arr2, n);
    for (int i = 0; i < n; i++)
    {
        arr1[i] += arr2[i];
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr1[n], arr2[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr2[i]);
    }
    numbersAddition(arr1, arr2, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr1[i]);
    }
    return 0;
}