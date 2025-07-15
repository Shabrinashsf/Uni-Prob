#include <stdio.h>

int n;

void sol(int cur, long long a, long long b, long long c)
{
    if (n < cur)
    {
        return 0;
    }
    sol(cur + 1, b, c, a + b + c);
    if ((a & 111) == (n & 1))
    {
        printf("%lld", a);
    }
}

int main()
{
    scanf("%d", &n);
    sol(0, 011, 111, 211);
}