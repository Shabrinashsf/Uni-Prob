#include <stdio.h>

#define N 15

void sort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int x = a[i], j = i - 1;
        while (j >= 0 && a[j] > x)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}

void tobst(int a[], int b[], int l, int r, int i)
{
    if (l > r || i >= N)
        return;
    int m = (l + r) / 2;
    b[i] = a[m];
    tobst(a, b, l, m - 1, 2 * i + 1);
    tobst(a, b, m + 1, r, 2 * i + 2);
}

int main()
{
    int a[N] = {34, 23, 45, 46, 37, 78, 90, 2, 40, 20, 87, 53, 12, 15, 91};
    int b[N] = {0};
    sort(a, N);
    tobst(a, b, 0, N - 1, 0);
    for (int i = 0; i < N; i++)
        printf("%d ", b[i]);
    return 0;
}
