#include <stdio.h>

double acceleration(double delta_v)
{
    // Untuk menghitung percepatan kereta
    // a = delta_v / (1 / 60)
    // a = delta * 60
    return (delta_v * 60);
}

double stop(double a)
{
    // Untuk menghitung berapa lama waktu yang dibutuhkan untuk keret berhenti
    // Rumus => t = (Vf - Vi)/a
    return (-200 / a);
}

void instructions()
{
    printf("Kereta peluru dengan kecepatan awal 200 mil/jam mengalami perlambatan sehingga kecepatannya menjadi 150 mil/jam\n");
    printf("Program ini akan menghitung percepatan dari kereta peluru dan waktu yang dibutuhkan kereta peluru untuk sepenuhnya berhenti\n");
}

int main()
{
    double delta_v = -50, a, time;
    instructions();
    a = acceleration(delta_v);
    time = stop(a);
    printf("Percepatan kereta peluru: %.lf mil/jam^2\n", a);
    printf("Waktu yang dibutuhkan agar kereta berhenti: %lf jam", time);
}
