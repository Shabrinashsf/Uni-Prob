#include <stdio.h>

int fact_calc(int number)
{
    int value = 1;
    for (int i = number; i >= 1; i--)
    {
        value *= i;
        if (i == 1)
        {
            printf("1 ");
        }
        else
        {
            printf("%d x ", i);
        }
    }
    return value;
}

int tambahanBintang(int number)
{
    if (number == 1)
    {
        printf("**");
        return 0;
    }
    tambahanBintang(number - 1);
}

int bintang(int number)
{
    if (number == 1)
    {
        printf("****************");
        return 0;
    }
    printf("**");
    tambahanBintang(number - 1);
    bintang(number - 1);
}

int main()
{
    int n;
    while (1)
    {
        printf("Enter an integer between 0 and 9 or -1 to quit => ");
        scanf("%d", &n);

        if (n == -1)
        {
            return 0;
        }
        else if (n > 9 || n < 0)
        {
            printf("Invalid entry\n");
            continue;
        }
        else if (n == 0)
        {
            printf("************");
            printf("\n");
            printf("* 0! = 1 *\n");
            printf("************\n");
            continue;
        }

        bintang(n);
        if (n == 4)
        {
            printf("*");
        }
        else if (n == 5 || n == 6)
        {
            printf("**");
        }
        else if (n == 7)
        {
            printf("***");
        }
        else if (n == 8)
        {
            printf("****");
        }
        else if (n == 9)
        {
            printf("*****");
        }
        printf("\n");
        printf("* %d! = ", n);
        int hasil = fact_calc(n);
        printf("= %d *\n", hasil);
        bintang(n);
        if (n == 4)
        {
            printf("*");
        }
        else if (n == 5 || n == 6)
        {
            printf("**");
        }
        else if (n == 7)
        {
            printf("***");
        }
        else if (n == 8)
        {
            printf("****");
        }
        else if (n == 9)
        {
            printf("*****");
        }
        printf("\n");
    }
}