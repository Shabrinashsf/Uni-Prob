#include <stdio.h>

int main()
{
    int m, n, side1, side2, hypotenuse;
    printf("Masukkan m dan n (Note: m > n):\n");
    scanf("%d %d", &m, &n);

    // Cek apakah m > n
    if (m <= n)
    {
        printf("Masukkan m > n\n");
        return 1;
    }

    side1 = (m * m) - (n * n);
    side2 = 2 * m * n;
    hypotenuse = (m * m) + (n * n);

    printf("Triple Pythagoras: %d %d %d\n", side1, side2, hypotenuse);
    return 0;
}