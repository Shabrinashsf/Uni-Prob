#include <stdio.h>

int main()
{
    double iterasi, k = 0;
    double pi = 0;
    printf("Enter the number of iterations:\n");
    scanf("%lf", &iterasi);
    for (int i = 1; i <= iterasi; i++)
    {
        pi = pi + (4 / (i + k) - 4 / (i + k + 2));
        k += 3;
    }
    printf("Value of x is: %lf\n", pi);
}
