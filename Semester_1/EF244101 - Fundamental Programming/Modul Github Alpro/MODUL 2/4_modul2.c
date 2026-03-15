#include <stdio.h>

int main()
{
    int k;
    int n[k];
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &n[i]);
    }
    for (int r = k; r > 1; r--)
    {
        printf("%d\n", n[r]);
    }
}