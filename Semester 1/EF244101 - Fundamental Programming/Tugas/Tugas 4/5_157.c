#include <stdio.h>
#include <math.h>

int main()
{
    int m, n, temp, gcd;
    printf("Enter two numbers:\n");
    scanf("%d %d", &m, &n);
    m = fabs(m);
    n = fabs(n);
    while (n != 0)
    {
        temp = n;
        n = m % n;
        m = temp;
    }
    gcd = m;
    printf("Great common diviser is: %d", gcd);
}