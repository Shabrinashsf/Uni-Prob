#include <stdio.h>
#include <math.h>

int main()
{
    double principal, iTahun, iBulan, monthlyPayment, temp;
    int n;

    printf("Enter the borrowed amount:\n");
    scanf("%lf", &principal);
    printf("Enter the annual interest rate:\n");
    scanf("%lf", &iTahun);
    printf("Enter the number of payments:\n");
    scanf("%d", &n);

    double bungaBulanan[n];
    double pokokBulanan[n];
    double sisaPokok[n];

    iTahun *= 0.01;
    iBulan = iTahun / 12;
    monthlyPayment = (principal * iBulan) / (1 - pow((1 + iBulan), -n));
    monthlyPayment = round(monthlyPayment * 100) / 100;

    temp = principal;
    for (int b = 0; b < n; b++)
    {
        bungaBulanan[b] = round(temp * iBulan * 100) / 100;
        pokokBulanan[b] = round((monthlyPayment - bungaBulanan[b]) * 100) / 100;
        sisaPokok[b] = round((temp - pokokBulanan[b]) * 100) / 100;
        temp = sisaPokok[b];

        if (b == n - 1)
        {
            pokokBulanan[b] = round((pokokBulanan[b] + sisaPokok[b]) * 100) / 100;
            sisaPokok[b] = 0.00;
            monthlyPayment = round((pokokBulanan[b] + bungaBulanan[b]) * 100) / 100;
        }
    }

    printf("Payment     Interest     Principal     Principal Balance\n");
    printf("--------------------------------------------------------\n");
    for (int a = 0; a < n; a++)
    {
        printf("%3c %d %5c %.2lf %5c %.2lf %5c %.2lf\n", ' ', a + 1, ' ', bungaBulanan[a], ' ', pokokBulanan[a], ' ', sisaPokok[a]);
    }
    printf("--------------------------------------------------------\n");
    printf("Final payment %2c $%.2lf", ' ', monthlyPayment);
}
