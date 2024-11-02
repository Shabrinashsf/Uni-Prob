// Write by Shabrina Amalia Safaana

#include <stdio.h>
#include <math.h>

int main()
{
    long long k, sn, m, n;
    scanf("%lld", &k);

    n = (long long)((-1 + sqrt(1 + 8.0 * k)) / 2);
    sn = (n * (n + 1)) / 2;

    if (sn < k)
    {
        n++;
        sn = (n * (n + 1)) / 2;
    }

    m = k - ((n * (n - 1)) / 2);

    printf("%lld %lld", m - 1, n);
}
