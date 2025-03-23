#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAMES 100
#define MAX_SURNAME_LENGTH 16
#define MAX_FIRST_LENGTH 11
#define MAX_MIDDLE_INIT_LENGTH 2
#define MAX_LINE_LENGTH 80

void process_line(char name[], int index, char surname[][MAX_SURNAME_LENGTH], char first[][MAX_FIRST_LENGTH], char middle_init[][MAX_MIDDLE_INIT_LENGTH])
{
    int lokasiComma = -1;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == ',')
        {
            lokasiComma = i;
            break;
        }
    }

    if (lokasiComma == -1)
    {
        printf("Format nama salah!\n");
        return;
    }

    int surname_length = lokasiComma < 15 ? lokasiComma : 15;
    strncpy(surname[index], name, surname_length);
    surname[index][surname_length] = '\0';

    int i = lokasiComma + 2;
    int first_length = 0;

    while (name[i] != ' ' && name[i] != '\0' && first_length < 10)
    {
        if (name[i] != '.')
        {
            first[index][first_length++] = name[i];
        }
        i++;
    }
    first[index][first_length] = '\0';

    if (name[i] == ' ')
    {
        i++;
        if (isalpha(name[i]) && name[i] != '.')
        {
            middle_init[index][0] = name[i];
            middle_init[index][1] = '\0';
        }
        else
        {
            middle_init[index][0] = '\0';
        }
    }
    else
    {
        middle_init[index][0] = '\0';
    }
}

void display_names(int count, char surname[][MAX_SURNAME_LENGTH], char first[][MAX_FIRST_LENGTH], char middle_init[][MAX_MIDDLE_INIT_LENGTH])
{
    printf("\nOutput:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-15s %-10s %s\n", surname[i], first[i], middle_init[i]);
    }
}

int main()
{
    char surname[MAX_NAMES][MAX_SURNAME_LENGTH];
    char first[MAX_NAMES][MAX_FIRST_LENGTH];
    char middle_init[MAX_NAMES][MAX_MIDDLE_INIT_LENGTH];
    char name[MAX_LINE_LENGTH];
    int nameSum = 0;

    printf("Enter names in the format 'Surname, First Middle' (enter 'q' to quit):\n");

    while (nameSum < MAX_NAMES)
    {
        printf("Enter name %d: ", nameSum + 1);

        if (!fgets(name, sizeof(name), stdin) || name[0] == 'q')
        {
            break;
        }

        name[strcspn(name, "\n")] = '\0';

        process_line(name, nameSum, surname, first, middle_init);
        nameSum++;
    }

    display_names(nameSum, surname, first, middle_init);
}
