#include <stdio.h>

long long gcd(long long a, long long b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int main()
{
    long long d, h;
    scanf("%lld %lld", &d, &h);
    printf("%lld", gcd(d, h));
}
