#include <stdio.h>
#include <math.h>

// Shabrina Amalia Safaana 5025241157

int main()
{
    double ekspresi;
    double batas;
    double nilaiX;

    for (double x = 1;; x += 1.0)
    {
        nilaiX = x;
        ekspresi = pow((2.0 * x + 1.0) / (2.0 * x - 1.0), x);
        batas = ekspresi - 2.718281;
        if (fabs(batas) < 0.000001)
        {
            break;
        }
    }

    printf("Nilai x yang membuat loop berhenti: %d\n", nilaiX);
    printf("Perkiraan nilai e yang dihitung oleh fungsi ekspresi: %.6lf\n", ekspresi);
    printf("Nilai e: 2.718281\n");
    printf("%.6lf", fabs(batas));
}