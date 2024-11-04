#include <stdio.h>

long long k(long long n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 2;
    }
    return 3 * k(n - 1);
}

int main()
{
    long long n;
    scanf("%lld", &n);
    printf("Ada %lld model, bebaskan aku!", k(n));
}