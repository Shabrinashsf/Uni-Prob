#include <stdio.h>
// cek apakah suatu bilangan dari 0 sampai 999 adalah bilangan armstrong

int main()
{
    int n, dig1, dig2, dig3, final;
    printf("Masukkan bilangan dari 0 sampai 999:\n");
    scanf("%d", &n);
    dig3 = n % 10;
    dig2 = (n / 10) % 10;
    dig1 = n / 100;
    // dig3 = satuan, dig2 = puluhan, dig1 = ratusan

    if (n >= 0 && n <= 999)
    {
        if (n == 0)
        {
            printf("Bukan Merupakan Bilangan Armstrong\n");
        }
        else if (n > 0 && n <= 9)
        {
            printf("Merupakan Bilangan Armstrong\n");
        }
        else if (n >= 10 && n <= 99)
        {
            printf("Bukan merupakan bilangan armstrong");
        }
        else
        {
            final = (dig1 * dig1 * dig1) + (dig2 * dig2 * dig2) + (dig3 * dig3 * dig3);
            if (final == n)
            {
                printf("Merupakan Bilangan Armstrong\n");
            }
            else
            {
                printf("Bukan merupakan Bilangan Armstrong\n");
            }
        }
    }
    else
    {
        return 0;
    }
}