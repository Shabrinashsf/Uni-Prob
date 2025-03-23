#include <stdio.h>
#include <math.h>

int main()
{
    int weekdayMenit, nightMenit, weekendMenit, totalMenit;
    double bill, tax, average;
    double chargeKerja, chargePekan, chargeMalam;
    double chargePlus = 40;
    scanf("%d %d %d", &weekdayMenit, &nightMenit, &weekendMenit);
    if (weekdayMenit > 600)
    {
        chargeKerja = 3999;
        chargeKerja += (weekdayMenit - 600) * 40;
    }
    else
    {
        chargeKerja = 3999;
    }

    totalMenit = weekdayMenit + nightMenit + weekendMenit;
    tax = chargeKerja * 0.0525;
    bill = chargeKerja + tax;
    average = chargeKerja / totalMenit;

    printf("==== Bill Summary ====\n");
    printf("Weekday minutes: %d minutes\n", weekdayMenit);
    printf("Night minutes: %d minutes\n", nightMenit);
    printf("Weekend minutes: %d minutes\n", weekendMenit);
    printf("Total minutes: %d minutes\n", totalMenit);
    printf("Pretax bill: %.2lf\n", chargeKerja / 100);
    printf("Average minute cost: %.2lf\n", average / 100);
    printf("Taxes: %.2lf\n", tax / 100);
    printf("Total bill: %.2lf\n", bill / 100);
}