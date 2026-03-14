#include <stdio.h>
// acc
int main()
{
    double x1, y1, x2, y2;
    double m;
    double b;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

    if (x2 == x1)
    {
        printf("-_-");
        return 0;
    }
    m = (y2 - y1) / (x2 - x1);
    b = y1 - (m * x1);
    printf("%.2f %.2f", m, b);
}