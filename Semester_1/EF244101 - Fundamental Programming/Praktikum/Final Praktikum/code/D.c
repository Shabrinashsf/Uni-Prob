#include <stdio.h>
#include <string.h>
// acc
int main()
{
    long long x;
    char nama[100];
    long long sum = 0;
    scanf("%s %lld", nama, &x);
    if (strcmp(nama, "Ellie") == 0)
    {
        if (x >= 2)
        {
            for (long long i = 2; i <= x; i += 2)
            {
                sum += i;
            }
        }
    }
    else if (strcmp(nama, "Oddie") == 0)
    {
        if (x >= 1)
        {
            for (long long i = 1; i <= x; i += 2)
            {
                sum += i;
            }
        }
    }
    else
    {
        printf("Who is that?\n");
        return 0;
    }
    printf("%lld\n", sum);
}
