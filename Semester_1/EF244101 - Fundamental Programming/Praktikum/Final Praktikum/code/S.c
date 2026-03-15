#include <stdio.h>
#define ONGKIR 50000
// acc
int main()
{
    int n;
    int k, after_diskon, diskon_ongkir, final;
    scanf("%d %d", &n, &k);

    if (n == 1)
        after_diskon = k - k * 35 / 100;
    else if (n == 2)
        after_diskon = k - k * 45 / 100;
    else if (n == 3)
        after_diskon = k - k * 50 / 100;
    else if (n == 4)
        after_diskon = k - k * 55 / 100;
    else if (n == 5)
        after_diskon = k - k * 40 / 100;
    else
        after_diskon = k;

    if (after_diskon >= 250000)
        diskon_ongkir = ONGKIR * 0;
    else if (after_diskon >= 150000)
        diskon_ongkir = ONGKIR - ONGKIR * 50 / 100;
    else if (after_diskon >= 50000)
        diskon_ongkir = ONGKIR - ONGKIR * 25 / 100;
    else
        diskon_ongkir = ONGKIR;

    final = after_diskon + diskon_ongkir;

    if (final > 300000)
    {
        printf("Mamaa minta uang, uangku kurang %d :((\n", final - 300000);
        printf("Totalnya tadi %d\n", final);
    }
    else if (final == 300000)
    {
        printf("Yeyyy totalnya pas 300000\n");
        printf("Mamaa, Surip udah gede ga jadi minta uang :)\n");
    }
    else if (final < 300000)
    {
        printf("WOHHHH uangku sisa %d\n", 300000 - final);
        printf("Mamaa Surip bisa kasi THR ke adek adek, tadi totalnya %d\n", final);
    }
}
