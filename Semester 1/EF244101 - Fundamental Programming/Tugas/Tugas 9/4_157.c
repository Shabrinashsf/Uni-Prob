#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 17

typedef struct
{
    char triplet[6];
    int mpn_index;
    int lower;
    int upper;
} mpn_table;

void load_Mpn_Table(FILE *file, mpn_table arr[], int max, int *actual_size)
{
    int count = 0;
    while (count < max && fscanf(file, "%5s %d %d %d", &arr[count].triplet, &arr[count].mpn_index, &arr[count].lower, &arr[count].upper) == 4)
    {
        count++;
    }
    fclose(file);
    *actual_size = count;
}

void search(mpn_table arr[], int size, char string[])
{
    int found = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr[i].triplet, string) == 0)
        {
            found = 1;
            printf("for %s, MPN = %d; 95%% of samples contain between %d and %d bacteria/ml\n", string, arr[i].mpn_index, arr[i].lower, arr[i].upper);
            break;
        }
    }
    if (!found)
    {
        printf("There are no match for %s\n", string);
    }
}

int main()
{
    mpn_table mpnTable[MAX_SIZE];
    int actual_size = 0;

    FILE *file = fopen("mpn_table.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    load_Mpn_Table(file, mpnTable, MAX_SIZE, &actual_size);

    while (1)
    {
        char out;
        char target[6];
        printf("Enter combination-of-positives triplet (ex: x-x-x): ");
        scanf("%s", target);
        search(mpnTable, actual_size, target);
        getchar();
        printf("Do another search? y/n: ");
        scanf("%c", &out);
        if (out == 'n')
        {
            break;
        }
    }
}