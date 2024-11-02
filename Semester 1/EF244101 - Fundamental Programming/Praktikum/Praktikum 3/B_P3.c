// Write by Shabrina Amalia Safaana

// pola aneh
#include <stdio.h>

long long tengah(long long x)
{
    long long temp = 0;
    for (long long i = 1; i <= x; i++)
    {
        temp += i;
    }
    return temp;
}

long long pola(long x)
{
    if (x == 0)
    {
        return 0;
    }
    else if (x == 1)
    {
        return 1;
    }
    return 2 * pola(x - 1) + tengah(x);
}

int main()
{
    long long input;
    scanf("%lld", &input);
    printf("%lld", pola(input));
}
