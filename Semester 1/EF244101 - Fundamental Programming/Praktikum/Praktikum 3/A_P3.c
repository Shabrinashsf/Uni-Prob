// Write by Shabrina Amalia Safaana

#include <stdio.h>

int fib(int a, int b, int x)
{
    if (a + b > x)
    {
        return b;
    }
    a + b - a - b + fib(b, a + b, x);
    printf("%d ", a + b);
}

int jumlah(int a, int b, int x)
{
    if (x == 0)
    {
        return 0;
    }
    else if (x == 1)
    {
        return 2;
    }
    if (a + b > x)
    {
        return 1;
    }
    return a + b + jumlah(b, a + b, x);
}

int main()
{
    int x;
    scanf("%d", &x);
    fib(0, 1, x);
    if (x == 0)
    {
        printf("0\n");
    }
    else
    {
        printf("1 0\n");
    }
    printf("%d", jumlah(0, 1, x));
}
