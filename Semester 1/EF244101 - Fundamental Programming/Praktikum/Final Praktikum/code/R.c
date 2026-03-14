#include <stdio.h>

#define M 1000000007

long long solve(long long x, long long y, long long a, long long b, long long n)
{
    if (n == 0)
    {
        return x % M;
    }
    if (n == 1)
    {
        return y % M;
    }

    long long bef2 = x % M;
    long long bef1 = y % M;
    long long now = 0;

    for (long long i = 2; i <= n; i++)
    {
        now = (a * bef1 % M + b * bef2 % M) % M;
        bef2 = bef1;
        bef1 = now;
    }

    return now;
}

int main()
{
    long long x, y, a, b, n;
    scanf("%lld %lld %lld %lld %lld", &x, &y, &a, &b, &n);
    printf("%lld\n", solve(x, y, a, b, n));
}
