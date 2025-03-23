#include <stdio.h>
#include <math.h>
// M = kecepatan maksimum dalam putaran per menit
// m = kecepatan minimum dalam putaran per menit
// fungsi speeds_ratio yang menghitung rasio dari any kecepatan maksimal dan minimal
// fungsi main = prompt maximum dan minimum speeds (rpm), memanggil fungsi speeds_ratio, menampilkan hasilnya dalam bentuk kalimat

// Fungsi untuk mencari speeds ratio
double speeds_ratio(double M, double m)
{
    double z = M / m;
    return (pow(z, 0.2));
}

int main()
{
    double max, min, ratio;
    printf("Enter the maximum speed in rpm:\n");
    scanf("%lf", &max);
    printf("Enter the minimum speed in rpm:\n");
    scanf("%lf", &min);

    // Memanggil fungsi speeds_ratio dengan parameter min dan max yang didapat dari input user
    ratio = speeds_ratio(max, min);
    printf("The ratio between successive speeds of a six-speed gearbox with maximum speed %.2lf rpm and minimum speed %.2lf rpm is %.2lf", max, min, ratio);
}