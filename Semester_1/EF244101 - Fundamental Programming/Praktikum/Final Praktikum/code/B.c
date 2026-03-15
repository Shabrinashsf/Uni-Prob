#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1001
// acc
typedef struct
{
    long long kode;
    char nama[300];
    long long harga;
    long long stok;
} makanan;

int main()
{
    makanan food[MAX_SIZE];
    memset(food, 0, sizeof(food));
    long long i = 0, income = 0;

    while (1)
    {
        char cmd[10];
        scanf("%s", cmd);

        if (strcmp(cmd, "ADD") == 0)
        {
            long long kode, harga, stok;
            char nama[100];
            scanf("%lld", &kode);
            scanf(" %[^\n]", nama);
            scanf("%lld %lld", &harga, &stok);

            int found = 0;

            for (int j = 0; j < i; j++)
            {
                if (food[j].kode == kode)
                {
                    found = 1;
                    printf("Menu is already exists\n");
                    break;
                }
            }

            if (!found)
            {
                printf("Menu added\n");
                food[i].kode = kode;
                strcpy(food[i].nama, nama);
                food[i].harga = harga;
                food[i].stok = stok;
                i++;
            }
        }
        else if (strcmp(cmd, "REMOVE") == 0)
        {
            long long kode_to_remove;
            scanf("%lld", &kode_to_remove);
            int found = 0;

            for (int j = 0; j < i; j++)
            {
                if (food[j].kode == kode_to_remove)
                {
                    found = 1;
                    for (int k = j; k < i - 1; k++)
                    {
                        food[k] = food[k + 1];
                    }
                    i--;
                    printf("Menu removed\n");
                    break;
                }
            }

            if (!found)
            {
                printf("Menu does not exist\n");
            }
        }
        else if (strcmp(cmd, "INFO") == 0)
        {
            long long kode_to_find;
            scanf("%lld", &kode_to_find);
            int found = 0;

            for (int j = 0; j < i; j++)
            {
                if (food[j].kode == kode_to_find)
                {
                    found = 1;
                    printf("#%lld %s\n", food[j].kode, food[j].nama);
                    printf("Price : Rp%lld\n", food[j].harga);
                    printf("Stock : %lldx\n", food[j].stok);
                    break;
                }
            }

            if (!found)
            {
                printf("Menu does not exist\n");
            }
        }
        else if (strcmp(cmd, "ORDER") == 0)
        {
            long long kode_to_order, jumlah;
            scanf("%lld %lld", &kode_to_order, &jumlah);
            int found = 0;

            for (int j = 0; j < i; j++)
            {
                if (food[j].kode == kode_to_order)
                {
                    found = 1;
                    if (jumlah <= 0)
                    {
                        printf("So you want to order or what\n");
                    }
                    else if (food[j].stok < jumlah)
                    {
                        printf("Apologize, the stock is not enough\n");
                    }
                    else
                    {
                        food[j].stok -= jumlah;
                        long long cost = jumlah * food[j].harga;
                        income += cost;
                        printf("Ordered %lldx %s for Rp%lld\n", jumlah, food[j].nama, cost);
                    }
                    break;
                }
            }

            if (!found)
            {
                printf("Menu does not exist\n");
            }
        }
        else if (strcmp(cmd, "CLOSE") == 0)
        {
            printf("Earnings: Rp%lld\n", income);
            printf("Informatics canteen is closing... thanks for the visit!\n");
            break;
        }
    }
}
