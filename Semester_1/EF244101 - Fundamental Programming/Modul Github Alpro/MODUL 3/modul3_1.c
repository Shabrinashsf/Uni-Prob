#include <stdio.h>
// faktorial
// 5! = 5 x 4 x 3 x 2 x 1

int faktorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * faktorial(n - 1);
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", faktorial(n));
}