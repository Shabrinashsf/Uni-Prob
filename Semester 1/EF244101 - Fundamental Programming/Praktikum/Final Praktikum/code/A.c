#include <stdio.h>
#include <math.h>

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
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long GCD = gcd(n, k);
    if (GCD == 1)
    {
        printf("%lld", ((n - 1) * n) / 2);
    }
    else
    {
        double temp_cycle = (double)n / (double)GCD;
        long long cycle = (long long)round(temp_cycle);

        long long temp = cycle * (2 + (cycle - 1) * GCD);
        printf("%lld\n", temp / 2);
    }
}

