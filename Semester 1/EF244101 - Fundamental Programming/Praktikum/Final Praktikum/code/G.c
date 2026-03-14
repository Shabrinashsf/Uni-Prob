#include <stdio.h>
#define MOD 1000000007

long long solve(long long n, long long a, long long b)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 2;
    if (n == 2)
        return (a + b) % MOD;
    if (n == 3)
        return 5;

    long long dp[n + 1];
    dp[0] = 1;
    dp[1] = 2;
    dp[2] = (a + b) % MOD;
    dp[3] = 5;

    for (long long i = 4; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            dp[i] = (a * dp[i - 2] + b) % MOD;
        }
        else
        {
            dp[i] = (4 * dp[i - 2] - 4 * dp[i - 4] + ((i - 1) * (i - 1) / 4)) % MOD;
        }
    }

    return dp[n];
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        long long a, b, n;
        scanf("%lld %lld %lld", &a, &b, &n);
        printf("%lld\n", solve(n, a, b));
    }
    return 0;
}
