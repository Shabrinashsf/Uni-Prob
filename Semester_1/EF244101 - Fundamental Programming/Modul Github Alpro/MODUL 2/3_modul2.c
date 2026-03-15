#include <stdio.h>

int main()
{
    int k, prime;
    scanf("%d", &k);
    if (k >= 1)
    {
        printf("* * ");
    }
    for (int p = 4; p <= k; p++)
    {
        prime = 0;
        for (int i = 2; i < p; i++)
        {
            if (p % i == 0)
            {
                printf("%d ", p);
                i = p;
                prime = 1;
            }
        }
        if (prime == 0)
        {
            printf("* ");
        }
    }
}
