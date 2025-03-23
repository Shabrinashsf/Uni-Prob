#include <stdio.h>

int within_x_percent(double ref, double data, double x)
{
    double batasBawah = ref - (x / 100.0) * ref;
    double batasAtas = ref + (x / 100.0) * ref;
    return data >= batasBawah && data <= batasAtas;
}

int main()
{
    double boiling_point;
    printf("Enter boiling point (in celcius degree):\n");
    scanf("%lf", &boiling_point);
    if (within_x_percent(100, boiling_point, 5))
    {
        printf("Substance: Water\n");
    }
    else if (within_x_percent(357, boiling_point, 5))
    {
        printf("Substance: Mercury\n");
    }
    else if (within_x_percent(1187, boiling_point, 5))
    {
        printf("Substance: Copper\n");
    }
    else if (within_x_percent(2193, boiling_point, 5))
    {
        printf("Substance: Silver\n");
    }
    else if (within_x_percent(2660, boiling_point, 5))
    {
        printf("Substance: Gold\n");
    }
    else
    {
        printf("Substance unknown\n");
    }
}