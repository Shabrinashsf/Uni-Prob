#include <stdio.h>

// Fungsi untuk cari tahu berapa temperatur (dalam celcius) pada kedalaman tertentu
double celcius(double depth)
{
    return (10 * depth + 20);
}

// Fungsi untuk konversi dari celcius menjadi fahrenheit
double fahrenheit(double celcius)
{
    return (1.8 * celcius + 32);
}

int main()
{
    double depth, C, F;
    printf("Masukkan kedalaman dalam kilometer:\n");
    scanf("%lf", &depth);

    // Memanggil fungsi celcius dengan parameter depth yang didapat dari input user
    C = celcius(depth);

    // Memanggil fungsi fahrenheit untuk mengonversi celcius menjadi fahrenheit
    F = fahrenheit(C);
    printf("Temperature pada kedalaman %lf dalam:\nDerajat celcius: %.2lf\nDerajat fahrenheit: %.2lf", depth, C, F);
}