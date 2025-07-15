#include <stdio.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
} posisi;

double manhattan(posisi *bunga, int banyakData)
{
    double min = __DBL_MAX__;
    for (int i = 0; i < banyakData; i++)
    {
        for (int j = i + 1; j < banyakData; j++)
        {
            double jarak = fabs(bunga[i].x - bunga[j].x) + fabs(bunga[i].y - bunga[j].y);
            if (jarak < min)
            {
                min = jarak;
            }
        }
    }
    return min;
}

double euclidean(posisi *bunga, int banyakData)
{
    double min = __DBL_MAX__;
    for (int i = 0; i < banyakData; i++)
    {
        for (int j = i + 1; j < banyakData; j++)
        {
            double jarak = sqrt(pow(bunga[i].x - bunga[j].x, 2) + pow(bunga[i].y - bunga[j].y, 2));
            if (jarak < min)
            {
                min = jarak;
            }
        }
    }
    return min;
}

int main()
{
    int n;
    scanf("%d", &n);

    posisi bunga[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &bunga[i].x, &bunga[i].y);
    }

    double minManhattan = manhattan(bunga, n);
    double minEuclidean = euclidean(bunga, n);

    double min = (minManhattan < minEuclidean) ? minManhattan : minEuclidean;

    printf("%.2lf", min);
}