#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[25];
    float max_speed;
    float wingspan;
    float length;
    char type;
    char description[80];
} aircraft;

void add_aircraft(const char *filename)
{
    FILE *file = fopen(filename, "ab");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    aircraft ac;
    printf("Add aircraft name: ");
    fgets(ac.name, 25, stdin);
    ac.name[strcspn(ac.name, "\n")] = 0;

    printf("Add aircraft max speed (km/h): ");
    scanf("%f", &ac.max_speed);

    printf("Add aircraft wingspan (m): ");
    scanf("%f", &ac.wingspan);

    printf("Add aircraft length (m): ");
    scanf("%f", &ac.length);

    printf("Add aircraft type (M for militer, C for sipil): ");
    getchar();
    scanf("%c", &ac.type);

    getchar();
    printf("Add description: ");
    fgets(ac.description, 80, stdin);
    ac.description[strcspn(ac.description, "\n")] = 0;

    fwrite(&ac, sizeof(aircraft), 1, file);
    fclose(file);

    printf("Aircraft data successfuly added.\n");
}

void search_by_name(const char *filename, char search_name[])
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    aircraft ac;
    int found = 0;
    while (fread(&ac, sizeof(aircraft), 1, file))
    {
        if (strcmp(ac.name, search_name) == 0)
        {
            printf("\n--- Aircraft data found ---\n");
            printf("Name: %s\n", ac.name);
            printf("Max cruise speed: %.2f km/h\n", ac.max_speed);
            printf("Wingspan: %.2f m\n", ac.wingspan);
            printf("Length: %.2f m\n", ac.length);
            printf("Type: %c\n", ac.type);
            printf("Description: %s\n", ac.description);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Aircraft with name '%s' not found.\n", search_name);
    }
    fclose(file);
}

void search_by_cruise_speed(const char *filename, float search_speed)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    aircraft ac;
    int found = 0;
    while (fread(&ac, sizeof(aircraft), 1, file))
    {
        if (ac.max_speed == search_speed)
        {
            printf("\n--- Aircraft data found ---\n");
            printf("Name: %s\n", ac.name);
            printf("Max cruise speed: %.2f km/h\n", ac.max_speed);
            printf("Wingspan: %.2f m\n", ac.wingspan);
            printf("Length: %.2f m\n", ac.length);
            printf("Type: %c\n", ac.type);
            printf("Description: %s\n", ac.description);
            found = 1;
        }
    }
    if (!found)
    {
        printf("There are no aircraft with max cruise speed %.2f km/h.\n", search_speed);
    }
    fclose(file);
}

void search_by_wingspan(const char *filename, float search_wingspan)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    aircraft ac;
    int found = 0;
    while (fread(&ac, sizeof(aircraft), 1, file))
    {
        if (ac.wingspan == search_wingspan)
        {
            printf("\n--- Aircraft data found ---\n");
            printf("Name: %s\n", ac.name);
            printf("Max cruise speed: %.2f km/h\n", ac.max_speed);
            printf("Wingspan: %.2f m\n", ac.wingspan);
            printf("Length: %.2f m\n", ac.length);
            printf("Type: %c\n", ac.type);
            printf("Description: %s\n", ac.description);
            found = 1;
        }
    }
    if (!found)
    {
        printf("There are bo aircraft with wingspan %.2f m.\n", search_wingspan);
    }
    fclose(file);
}

void search_by_length(const char *filename, float search_length)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    aircraft ac;
    int found = 0;
    while (fread(&ac, sizeof(aircraft), 1, file))
    {
        if (ac.length == search_length)
        {
            printf("\n--- Aircraft data found ---\n");
            printf("Name: %s\n", ac.name);
            printf("Max cruise speed: %.2f km/h\n", ac.max_speed);
            printf("Wingspan: %.2f m\n", ac.wingspan);
            printf("Length: %.2f m\n", ac.length);
            printf("Type: %c\n", ac.type);
            printf("Description: %s\n", ac.description);
            found = 1;
        }
    }
    if (!found)
    {
        printf("There are no aircraft with length %.2f m.\n", search_length);
    }
    fclose(file);
}

void search_by_type(const char *filename, char search_type)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    aircraft ac;
    int found = 0;
    while (fread(&ac, sizeof(aircraft), 1, file))
    {
        if (ac.type == search_type)
        {
            printf("\n--- Aircraft data found ---\n");
            printf("Name: %s\n", ac.name);
            printf("Max cruise speed: %.2f km/h\n", ac.max_speed);
            printf("Wingspan: %.2f m\n", ac.wingspan);
            printf("Length: %.2f m\n", ac.length);
            printf("Type: %c\n", ac.type);
            printf("Description: %s\n", ac.description);
            found = 1;
        }
    }
    if (!found)
    {
        printf("There are no aircraft with type '%c'.\n", search_type);
    }
    fclose(file);
}

void display_all(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Failed to open file.\n");
        return;
    }

    printf("\n--- Semua Data Pesawat ---\n");
    aircraft ac;
    while (fread(&ac, sizeof(aircraft), 1, file))
    {
        printf("\n--- Aircraft data found ---\n");
        printf("Name: %s\n", ac.name);
        printf("Max cruise speed: %.2f km/h\n", ac.max_speed);
        printf("Wingspan: %.2f m\n", ac.wingspan);
        printf("Length: %.2f m\n", ac.length);
        printf("Type: %c\n", ac.type);
        printf("Description: %s\n", ac.description);
    }
    fclose(file);
}

int main()
{
    const char *filename = "aircraft.bin";
    int select;
    do
    {
        printf("\n--- Aircraft database system menu ---\n");
        printf("\n--- Select the number only ---\n");
        printf("1. Add aircraft\n");
        printf("2. Find aircraft by name\n");
        printf("3. Find aircraft by max speed\n");
        printf("4. Find aircraft by wingspan\n");
        printf("5. Find aircraft by length\n");
        printf("6. Find aircraft by type\n");
        printf("7. Display all aircraft data\n");
        printf("8. Finish\n");
        printf("Select: ");
        scanf("%d", &select);
        getchar();

        char search_name[25] = {};
        float search_max_speed = 0.0;
        float search_wingspan = 0.0;
        float search_length = 0.0;
        char search_type = 0;

        switch (select)
        {
        case 1:
            add_aircraft(filename);
            break;
        case 2:
            printf("Enter aircraft name you want to find: ");
            fgets(search_name, 25, stdin);
            search_name[strcspn(search_name, "\n")] = 0;
            search_by_name(filename, search_name);
            break;
        case 3:
            printf("Enter aircraft max speed you want to find: ");
            scanf("%f", &search_max_speed);
            search_by_cruise_speed(filename, search_max_speed);
            break;
        case 4:
            printf("Enter aircraft wingspan you want to find: ");
            scanf("%f", &search_wingspan);
            search_by_wingspan(filename, search_wingspan);
            break;
        case 5:
            printf("Enter aircraft length you want to find: ");
            scanf("%f", &search_length);
            search_by_length(filename, search_length);
            break;
        case 6:
            printf("Enter aircraft type you want to find: ");
            scanf("%c", &search_type);
            search_by_type(filename, search_type);
            break;
        case 7:
            display_all(filename);
            break;
        case 8:
            printf("Out from program.\n");
            break;
        default:
            printf("Your choice is not valid.\n");
        }
    } while (select != 8);
}