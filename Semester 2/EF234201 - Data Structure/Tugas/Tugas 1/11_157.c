#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct
{
    char name[50];
    double total_income;
    double total_expenses;
    double total_net_income; // income - expenses
    int total_stall;
} stall;

void add_data(stall data[MAX], int *id)
{
    char opsi;
    do
    {
        char tempName[50];
        double tempIncome, tempExpenses, tempNetIncome;
        printf("Enter the stall's name, income earned, and its expenses (ex: Games 2300.00 10000.00): ");
        scanf("%s %lf %lf", tempName, &tempIncome, &tempExpenses);
        tempNetIncome = tempIncome - tempExpenses;

        int found = 0;
        for (int i = 0; i < *id; i++)
        {
            if (strcmp(data[i].name, tempName) == 0)
            {
                data[i].total_income += tempIncome;
                data[i].total_expenses += tempExpenses;
                data[i].total_net_income += tempNetIncome;
                data[i].total_stall += 1;
                printf("Successfully update data!\n");
                found = 1;
                break;
            }
        }
        if (!found)
        {
            strcpy(data[*id].name, tempName);
            data[*id].total_income = tempIncome;
            data[*id].total_expenses = tempExpenses;
            data[*id].total_net_income = tempNetIncome;
            data[*id].total_stall = 1;
            (*id)++;
            printf("Successfully add new data!\n");
        }

        printf("Do you want to add another data? (Y/N): ");
        scanf(" %c", &opsi);
    } while (opsi == 'Y' || opsi == 'y');
}

int compare(const void *a, const void *b)
{
    stall *p1 = (stall *)a;
    stall *p2 = (stall *)b;

    if (p2->total_net_income > p1->total_net_income)
        return 1;
    if (p2->total_net_income < p1->total_net_income)
        return -1;
    return 0;
}

void main()
{
    stall data[100];
    int id = 0;
    add_data(data, &id);

    qsort(data, id, sizeof(stall), compare);

    printf("Profitable stalls (descending)\n");
    printf("%-15s %-12s %-18s %-14s %-15s\n", "Stall's name", "Total stall", "Total net income", "Total income", "Total expenses");
    for (int i = 0; i < id; i++)
    {
        printf("%-15s %-12d %-18.2lf %-14.2lf %-15.2lf\n", data[i].name, data[i].total_stall, data[i].total_net_income, data[i].total_income, data[i].total_expenses);
    }
    printf("The most profitable stall is %s\n", data[0].name);
}