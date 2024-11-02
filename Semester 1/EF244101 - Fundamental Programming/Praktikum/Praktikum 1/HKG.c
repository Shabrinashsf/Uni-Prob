// Write by Shabrina Amalia Safaana

#include <stdio.h>

int main()
{
    char n;
    scanf("%c", &n);

    if ((n % 2) == 0)
    {
        printf("%c adalah genap.", n);
    }
    else
    {
        printf("%c adalah ganjil.", n);
    }
}
