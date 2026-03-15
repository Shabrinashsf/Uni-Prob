#include <stdio.h>
#include <math.h>

int pola(int x)
{
    if (x == 0)
    {
        return 0;
    }
    return pow(x, 2) + pola(x - 1);
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", pola(n));
}