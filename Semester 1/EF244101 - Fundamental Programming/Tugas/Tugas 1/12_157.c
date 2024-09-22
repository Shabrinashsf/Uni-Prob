#include <stdio.h>

int main()
{
    double v, a, t, s, vt;
    printf("Jet fighter's velocity (km/hr):\n");
    scanf("%lf", &v);
    printf("Distance (meter):\n");
    scanf("%lf", &s);

    // Ubah kecepatan dari km/hr menjadi m/s
    vt = (v * 1000) / 3600;

    // Hitung percepatan jet (subtitusi t dari pers v = at ke pers s = 1/2at^2)
    a = (vt * vt) / (2 * s);

    // Hitung waktu yang dibutuhkan jet dari keadaan diam ke keadaan lepas landas
    t = vt / a;

    printf("Jet fighter acceleration: %.2lf m/s^2\n", a);
    printf("Accelerated time to takeoff speed: %.2lf sekon\n", t);
    return 0;
}