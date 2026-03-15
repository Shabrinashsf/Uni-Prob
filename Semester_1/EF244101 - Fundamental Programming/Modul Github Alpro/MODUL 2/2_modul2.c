#include <stdio.h>

int main()
{
    int k;
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        if ((i % 2) != 0)
        {
            printf("%d ", i);
        }
        else
        {
            printf("* ");
        }
    }
}