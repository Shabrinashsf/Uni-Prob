#include <stdio.h>
#include <math.h>

void drag_force(double *a, double *cd, double *v, double *p, double *force)
{
    *force = 0.5 * (*cd * *a * *p * pow(*v, 2));
}

int main()
{
    double f, cd, a, v;
    double p = 1.23;
    printf("Enter A value:\n");
    scanf("%lf", &a);
    printf("Enter CD value:\n");
    scanf("%lf", &cd);
    for (v = 0; v <= 40;)
    {
        if (v == 0)
        {
            printf("Velocity (m/s) %3c Force(newton)\n", ' ');
            printf("==================================\n");
        }

        drag_force(&a, &cd, &v, &p, &f);
        printf("%2c %.2lf %12c %.2lf\n", ' ', v, ' ', f);
        v += 5;
    }
}