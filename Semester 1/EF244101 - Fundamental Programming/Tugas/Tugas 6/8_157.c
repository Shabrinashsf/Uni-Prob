#include <stdio.h>

int main()
{
    float currentYear[12];
    float previousYear[12];
    float totalThisYear = 0;
    float totalLastYear = 0;
    float averageMonthThisYear;
    float averageMonthLastYear;

    printf("Input current year's rainfall for a month, and the second number will be what fell during the same month the previous year:\n");
    printf("For example: (xx.xx) (yy.yy)\n");
    printf("(current year's rainfall) (previous year's rainfall) in january and so on\n");
    printf("\n");
    printf("Please enter the data:\n");
    for (int i = 0; i < 12; i++)
    {
        scanf("%f %f", &currentYear[i], &previousYear[i]);
    }

    for (int i = 0; i < 12; i++)
    {
        totalThisYear += currentYear[i];
        totalLastYear += previousYear[i];
    }

    averageMonthThisYear = totalThisYear / 12.0;
    averageMonthLastYear = totalLastYear / 12.0;

    // lagi lagi tabel
    printf("%70c %s\n", ' ', " Table of monthly rainfall");
    printf("%15c %s %4c %s %4c %s %6c %s %7c %s %7c %s %7c %s %6c %s %4c %s %3c %s %3c %s %4c %s\n", ' ', "January", ' ', "February", ' ', "March", ' ', "April", ' ', "May", ' ', "June", ' ', "July", ' ', "August", ' ', "September", ' ', "October", ' ', "November", ' ', "December");
    printf("%s %7c", "This year", ' ');
    for (int i = 0; i < 12; i++)
    {
        printf("%.2f %7c", currentYear[i]);
    }
    printf("\n");
    printf("%s %7c", "Last year", ' ');
    for (int i = 0; i < 12; i++)
    {
        printf("%.2f %7c", previousYear[i]);
    }
    printf("\n");

    printf("Total rainfall this year: %2c %.2f\n", ' ', totalThisYear);
    printf("Total rainfall last year: %2c %.2f\n", ' ', totalLastYear);
    printf("Average monthly rainfall for this year: %2c %.2f\n", ' ', averageMonthThisYear);
    printf("Average monthly rainfall for last year: %2c %.2f\n", ' ', averageMonthLastYear);
}