// Made by Shabrina Amalia

#include <stdio.h>

int main()
{
    double x1, x2, x3, y1, y2, y3, m1, m2, b;

    printf("Masukkan titik 1 (x1, y1):\n");
    scanf("%lf %lf", &x1, &y1);
    printf("Masukkan titik 2 (x2, y2):\n");
    scanf("%lf %lf", &x2, &y2);
    printf("Hasil:\n");

    // Cari gradien m1 (gradien dari garis yang dibentuk oleh titik-titik yang diinput user)
    m1 = (y2 - y1) / (x2 - x1);

    // Cari titik tengah (x3, y3), titik tengah dari titik titik yang diinput user
    x3 = 0.5 * (x1 + x2);
    y3 = 0.5 * (y1 + y2);

    // Cari gradien m2 (gradien yang tegak lurus dengan m1)
    m2 = -1 / m1;

    // Masukan ke dalam rumus y - y3 = m * (x - x3)
    // Sehingga format outputnya y = mx + b
    b = (-m2 * x3) + y3;

    printf("Titik asal: (%.lf,%.lf) dan (%.lf,%.lf)\n", x1, y1, x2, y2);
    printf("y = %.2lfx + %.2lf", m2, b);
    return 0;
}

/*program ini akan fail ketika:
1. Inputan merupakan titik-titik yang sama, gradien m1 akan menghasilkan operasi pembagian dengan nol, yang menyebabkan error. (0,0) dan (0,0), (1,1) dan (1,1), (2,2) dan (2,2), dan seterusnya.
2. Kedua inputan titik membentuk garis horizontal: Jika garis antara dua titik adalah horizontal (misalnya, 𝑦1==𝑦2), gradien m1 akan menjadi nol menyebabkan m2 menjadi tak terdefinisi. contohnya (2, 0) dan (3, 0)
*/
