#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_peserta 8

typedef struct
{
    char name[50];
    float distance;
} jumper;

typedef struct
{
    char name[50];
    float best;
} best_jumper_individu;

int compare(const void *a, const void *b)
{
    best_jumper_individu *p1 = (best_jumper_individu *)a;
    best_jumper_individu *p2 = (best_jumper_individu *)b;

    if (p2->best > p1->best)
        return 1;
    if (p2->best < p1->best)
        return -1;
    return 0;
}

void best_jumper(best_jumper_individu newdata[max_peserta], float data1, float data2, float data3, int i, char name[50])
{
    float best = data1;
    if (data2 > best)
    {
        best = data2;
    }
    if (data3 > best)
    {
        best = data3;
    }
    strcpy(newdata[i].name, name);
    newdata[i].best = best;
}

void find_best(jumper data[max_peserta * 3], best_jumper_individu newdata[max_peserta])
{
    for (int i = 0; i < max_peserta; i++)
    {
        char name[50];
        strcpy(name, data[i].name);
        best_jumper(newdata, data[i].distance, data[i + 8].distance, data[i + 16].distance, i, name);
    }
}

void main()
{
    FILE *file;
    jumper data[max_peserta * 3];
    best_jumper_individu newdata[max_peserta];

    int count = 0;

    file = fopen("10_157.txt", "r");
    if (file == NULL)
    {
        printf("Gagal membuka file 10_157.txt\n");
        return;
    }

    while (count < max_peserta * 3 && fscanf(file, "%s %f", data[count].name, &data[count].distance) == 2)
    {
        count++;
    }

    fclose(file);

    find_best(data, newdata);

    qsort(newdata, max_peserta, sizeof(best_jumper_individu), compare);

    printf("Best jumper (descending)\n");
    for (int i = 0; i < max_peserta; i++)
    {
        printf("%s - %.2f meter\n", newdata[i].name, newdata[i].best);
    }
}