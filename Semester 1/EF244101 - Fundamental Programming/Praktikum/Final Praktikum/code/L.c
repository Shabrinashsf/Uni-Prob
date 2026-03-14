#include <stdio.h>
#include <math.h>
// acc
#define PI 3.14159265358979323846

int main()
{
    long double v, r, lp;
    scanf("%Lf", &v);
    r = cbrtl(v / (2 * PI));
    lp = 6 * PI * r * r;
    printf("Luas permukaan: %.2Lf\n", lp);
}
