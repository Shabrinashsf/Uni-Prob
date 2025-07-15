#include <stdio.h>
#include <string.h>

#define MAX_ISLAND 50
#define MAX_FARM_ISLAND 5

typedef struct
{
    char islandName[33];
    long islandX;
    long islandZ;
    int jumlah_farm;
    char farms[MAX_FARM_ISLAND][33];
    long farmRates[MAX_FARM_ISLAND];
} pulau;

typedef struct
{
    char islandFarm[33];
    char islandName[33];
    long farmRate;
} peternakan;

int main()
{
    pulau island[MAX_ISLAND];
    int jumlah_pulau = 0;

    for (int k = 0; k < MAX_ISLAND; k++)
    {
        island[k].jumlah_farm = 0;
    }

    while (1)
    {
        char cmd[17];
        scanf("%s", cmd);

        if (strcmp(cmd, "ADD_ISLAND") == 0)
        {
            if (jumlah_pulau < MAX_ISLAND)
            {
                scanf("%s %ld %ld", island[jumlah_pulau].islandName, &island[jumlah_pulau].islandX, &island[jumlah_pulau].islandZ);
                island[jumlah_pulau].jumlah_farm = 0;
                jumlah_pulau++;
                printf("ISLAND ADDED\n");
            }
            else
            {
                printf("CANNOT ADD MORE ISLAND\n");
            }
        }
        else if (strcmp(cmd, "ADD_FARM") == 0)
        {
            char farmName[33], islandName[33];
            long farmRate;
            scanf("%s %s %ld", farmName, islandName, &farmRate);

            int found = 0;
            for (int i = 0; i < jumlah_pulau; i++)
            {
                if (strcmp(island[i].islandName, islandName) == 0)
                {
                    if (island[i].jumlah_farm < MAX_FARM_ISLAND)
                    {
                        strcpy(island[i].farms[island[i].jumlah_farm], farmName);
                        island[i].farmRates[island[i].jumlah_farm] = farmRate;
                        island[i].jumlah_farm++;
                        printf("FARM ADDED\n");
                    }
                    else
                    {
                        printf("CANNOT ADD MORE FARMS TO THIS ISLAND\n");
                    }
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                printf("ISLAND NOT FOUND CANNOT ADD FARM\n");
            }
        }
        else if (strcmp(cmd, "VIEW_ALL") == 0)
        {
            for (int i = 0; i < jumlah_pulau; i++)
            {
                printf("ISLAND %s has %d farms:\n", island[i].islandName, island[i].jumlah_farm);
                for (int j = 0; j < island[i].jumlah_farm; j++)
                {
                    printf("FARM %s %ld\n", island[i].farms[j], island[i].farmRates[j]);
                }
            }
        }
        else
        {
            printf("INVALID COMMAND, BYE!\n");
            break;
        }
    }

    return 0;
}
