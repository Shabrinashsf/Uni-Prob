#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1001

typedef struct
{
    char flight_number[7];
    char city_departure[256];
    char destination[256];
    char date_of_departure[11];
    char time_of_departure[9];
    char date_of_arrival[11];
    char time_of_arrival[9];
    int first_class_seat_avail;
    int first_class_seat_sold;
    int coach_seat_avail;
    int coach_seat_sold;
} AIRLINE;

void create_flight(const char *file);
void delete_flight(const char *file, const char *flight_number);
void update_flight(const char *file, const char *flight_number);
void make_reservation(const char *file, const char *flight_number, int first_class, int coach);
void cancel_reservation(const char *file, const char *flight_number, int first_class, int coach);
void display_flights(const char *file);

int main()
{
    const char *file = "airline_database.txt";
    int choice;

    do
    {
        printf("\n--- Airlane Reservation System ---\n");
        printf("1. Create Flight\n");
        printf("2. Delete Flight\n");
        printf("3. Update Flight\n");
        printf("4. Make Reservation\n");
        printf("5. Cancel Reservation\n");
        printf("6. Display Flights\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        char flight_number[7];
        int first_class, coach;

        switch (choice)
        {
        case 1:
            create_flight(file);
            break;
        case 2:
            printf("Enter flight number to delete: ");
            scanf("%6s", flight_number);
            delete_flight(file, flight_number);
            break;
        case 3:
            printf("Enter flight number to update: ");
            scanf("%6s", flight_number);
            update_flight(file, flight_number);
            break;
        case 4:
            printf("Enter flight number to make a reservation: ");
            scanf("%6s", flight_number);
            printf("Enter number of first-class seats to reserve: ");
            scanf("%d", &first_class);
            printf("Enter number of coach seats to reserve: ");
            scanf("%d", &coach);
            make_reservation(file, flight_number, first_class, coach);
            break;
        case 5:
            printf("Enter flight number to cancel reservation: ");
            scanf("%6s", flight_number);
            printf("Enter number of first-class seats to cancel: ");
            scanf("%d", &first_class);
            printf("Enter number of coach seats to cancel: ");
            scanf("%d", &coach);
            cancel_reservation(file, flight_number, first_class, coach);
            break;
        case 6:
            display_flights(file);
            break;
        case 7:
            printf("Exiting system.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);

    return 0;
}

void create_flight(const char *file)
{
    FILE *fp = fopen(file, "a");
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    AIRLINE flight;
    printf("Enter flight number: ");
    scanf("%6s", flight.flight_number);
    printf("Enter departure city: ");
    scanf(" %[^\n]", flight.city_departure);
    printf("Enter destination city: ");
    scanf(" %[^\n]", flight.destination);
    printf("Enter departure date (YYYY-MM-DD): ");
    scanf("%s", flight.date_of_departure);
    printf("Enter departure time (HH:MM:SS): ");
    scanf("%s", flight.time_of_departure);
    printf("Enter arrival date (YYYY-MM-DD): ");
    scanf("%s", flight.date_of_arrival);
    printf("Enter arrival time (HH:MM:SS): ");
    scanf("%s", flight.time_of_arrival);
    printf("Enter number of first-class seats available: ");
    scanf("%d", &flight.first_class_seat_avail);
    flight.first_class_seat_sold = 0;
    printf("Enter number of coach seats available: ");
    scanf("%d", &flight.coach_seat_avail);
    flight.coach_seat_sold = 0;

    if (flight.first_class_seat_avail < 0 || flight.coach_seat_avail < 0)
    {
        printf("Invalid seat count.\n");
        return;
    }

    fprintf(fp, "%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
            flight.flight_number,
            flight.city_departure,
            flight.destination,
            flight.date_of_departure,
            flight.time_of_departure,
            flight.date_of_arrival,
            flight.time_of_arrival,
            flight.first_class_seat_avail,
            flight.first_class_seat_sold,
            flight.coach_seat_avail,
            flight.coach_seat_sold);

    printf("Flight added successfully.\n");

    fclose(fp);
}

void delete_flight(const char *file, const char *flight_number)
{
    FILE *fp = fopen(file, "r");
    if (!fp)
    {
        printf("Error opening the file '%s'.\n", file);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    AIRLINE flight;
    int found = 0;

    while (fscanf(fp, "%6s|%255[^|]|%255[^|]|%10[^|]|%8[^|]|%10[^|]|%8[^|]|%d|%d|%d|%d\n",
                  flight.flight_number,
                  flight.city_departure,
                  flight.destination,
                  flight.date_of_departure,
                  flight.time_of_departure,
                  flight.date_of_arrival,
                  flight.time_of_arrival,
                  &flight.first_class_seat_avail,
                  &flight.first_class_seat_sold,
                  &flight.coach_seat_avail,
                  &flight.coach_seat_sold) != EOF)
    {
        if (strcmp(flight.flight_number, flight_number) != 0)
        {
            fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
                    flight.flight_number,
                    flight.city_departure,
                    flight.destination,
                    flight.date_of_departure,
                    flight.time_of_departure,
                    flight.date_of_arrival,
                    flight.time_of_arrival,
                    flight.first_class_seat_avail,
                    flight.first_class_seat_sold,
                    flight.coach_seat_avail,
                    flight.coach_seat_sold);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove(file);
        rename("temp.txt", file);
        printf("Flight deleted successfully.\n");
    }
    else
    {
        printf("Flight not found.\n");
    }
}

void update_flight(const char *file, const char *flight_number)
{
    FILE *fp = fopen(file, "r");
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    AIRLINE flight;
    int found = 0;

    while (fscanf(fp, "%6s|%255[^|]|%255[^|]|%10[^|]|%8[^|]|%10[^|]|%8[^|]|%d|%d|%d|%d\n",
                  flight.flight_number,
                  flight.city_departure,
                  flight.destination,
                  flight.date_of_departure,
                  flight.time_of_departure,
                  flight.date_of_arrival,
                  flight.time_of_arrival,
                  &flight.first_class_seat_avail,
                  &flight.first_class_seat_sold,
                  &flight.coach_seat_avail,
                  &flight.coach_seat_sold) != EOF)
    {
        if (strcmp(flight.flight_number, flight_number) != 0)
        {
            fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
                    flight.flight_number,
                    flight.city_departure,
                    flight.destination,
                    flight.date_of_departure,
                    flight.time_of_departure,
                    flight.date_of_arrival,
                    flight.time_of_arrival,
                    flight.first_class_seat_avail,
                    flight.first_class_seat_sold,
                    flight.coach_seat_avail,
                    flight.coach_seat_sold);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);

    if (found)
    {
        AIRLINE new_flight;
        printf("Enter new departure city: ");
        scanf(" %[^\n]", new_flight.city_departure);
        printf("Enter new destination city: ");
        scanf(" %[^\n]", new_flight.destination);
        printf("Enter new departure date (YYYY-MM-DD): ");
        scanf("%s", new_flight.date_of_departure);
        printf("Enter new departure time (HH:MM:SS): ");
        scanf("%s", new_flight.time_of_departure);
        printf("Enter new arrival date (YYYY-MM-DD): ");
        scanf("%s", new_flight.date_of_arrival);
        printf("Enter new arrival time (HH:MM:SS): ");
        scanf("%s", new_flight.time_of_arrival);
        printf("Enter new number of first-class seats available: ");
        scanf("%d", &new_flight.first_class_seat_avail);
        printf("Enter new number of coach seats available: ");
        scanf("%d", &new_flight.coach_seat_avail);
        new_flight.first_class_seat_sold = 0;
        new_flight.coach_seat_sold = 0;

        fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
                flight_number,
                new_flight.city_departure,
                new_flight.destination,
                new_flight.date_of_departure,
                new_flight.time_of_departure,
                new_flight.date_of_arrival,
                new_flight.time_of_arrival,
                new_flight.first_class_seat_avail,
                new_flight.first_class_seat_sold,
                new_flight.coach_seat_avail,
                new_flight.coach_seat_sold);

        printf("Flight updated successfully.\n");
    }
    else
    {
        printf("Flight not found.\n");
    }

    fclose(temp);
    remove(file);
    rename("temp.txt", file);
}

void make_reservation(const char *file, const char *flight_number, int first_class, int coach)
{
    FILE *fp = fopen(file, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp)
    {
        printf("Error opening files.\n");
        if (fp)
            fclose(fp);
        if (temp)
            fclose(temp);
        return;
    }

    AIRLINE flight;
    int found = 0;

    while (fscanf(fp, "%6s|%255[^|]|%255[^|]|%10[^|]|%8[^|]|%10[^|]|%8[^|]|%d|%d|%d|%d\n",
                  flight.flight_number,
                  flight.city_departure,
                  flight.destination,
                  flight.date_of_departure,
                  flight.time_of_departure,
                  flight.date_of_arrival,
                  flight.time_of_arrival,
                  &flight.first_class_seat_avail,
                  &flight.first_class_seat_sold,
                  &flight.coach_seat_avail,
                  &flight.coach_seat_sold) != EOF)
    {
        if (strcmp(flight.flight_number, flight_number) == 0)
        {
            found = 1;
            if (flight.first_class_seat_avail >= first_class && flight.coach_seat_avail >= coach)
            {
                flight.first_class_seat_avail -= first_class;
                flight.first_class_seat_sold += first_class;
                flight.coach_seat_avail -= coach;
                flight.coach_seat_sold += coach;

                printf("Reservation made successfully.\n");
            }
            else
            {
                printf("Not enough seats available.\n");
            }
        }

        fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
                flight.flight_number,
                flight.city_departure,
                flight.destination,
                flight.date_of_departure,
                flight.time_of_departure,
                flight.date_of_arrival,
                flight.time_of_arrival,
                flight.first_class_seat_avail,
                flight.first_class_seat_sold,
                flight.coach_seat_avail,
                flight.coach_seat_sold);
    }

    fclose(fp);
    fclose(temp);

    if (!found)
    {
        printf("Flight not found.\n");
        remove("temp.txt");
    }
    else
    {
        remove(file);
        rename("temp.txt", file);
    }
}

void cancel_reservation(const char *file, const char *flight_number, int first_class, int coach)
{
    FILE *fp = fopen(file, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp)
    {
        printf("Error opening files.\n");
        if (fp)
            fclose(fp);
        if (temp)
            fclose(temp);
        return;
    }

    AIRLINE flight;
    int found = 0;

    while (fscanf(fp, "%6s|%255[^|]|%255[^|]|%10[^|]|%8[^|]|%10[^|]|%8[^|]|%d|%d|%d|%d\n",
                  flight.flight_number,
                  flight.city_departure,
                  flight.destination,
                  flight.date_of_departure,
                  flight.time_of_departure,
                  flight.date_of_arrival,
                  flight.time_of_arrival,
                  &flight.first_class_seat_avail,
                  &flight.first_class_seat_sold,
                  &flight.coach_seat_avail,
                  &flight.coach_seat_sold) != EOF)
    {
        if (strcmp(flight.flight_number, flight_number) == 0)
        {
            found = 1;
            if (flight.first_class_seat_sold >= first_class && flight.coach_seat_sold >= coach)
            {
                flight.first_class_seat_avail += first_class;
                flight.first_class_seat_sold -= first_class;
                flight.coach_seat_avail += coach;
                flight.coach_seat_sold -= coach;

                printf("Reservation cancelled successfully.\n");
            }
            else
            {
                printf("No reservation to cancel.\n");
            }
        }

        fprintf(temp, "%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%d\n",
                flight.flight_number,
                flight.city_departure,
                flight.destination,
                flight.date_of_departure,
                flight.time_of_departure,
                flight.date_of_arrival,
                flight.time_of_arrival,
                flight.first_class_seat_avail,
                flight.first_class_seat_sold,
                flight.coach_seat_avail,
                flight.coach_seat_sold);
    }

    fclose(fp);
    fclose(temp);

    if (!found)
    {
        printf("Flight not found.\n");
        remove("temp.txt");
    }
    else
    {
        remove(file);
        rename("temp.txt", file);
    }
}

void display_flights(const char *file)
{
    FILE *fp = fopen(file, "r");
    if (!fp)
    {
        printf("Error opening file.\n");
        return;
    }

    AIRLINE flight;
    printf("\n--- Flight Information ---\n");

    // Header tabel
    printf("%-8s %-25s %-25s %-12s %-10s %-12s %-10s %-10s %-10s %-10s %-10s\n",
           "Flight", "Departure City", "Destination", "Dep Date", "Dep Time",
           "Arr Date", "Arr Time", "FC Avail", "FC Sold", "Coach Avail", "Coach Sold");
    printf("==========================================================================================================================================================\n");

    // Membaca dan mencetak data
    while (fscanf(fp, "%6s|%255[^|]|%255[^|]|%10[^|]|%8[^|]|%10[^|]|%8[^|]|%d|%d|%d|%d\n",
                  flight.flight_number,
                  flight.city_departure,
                  flight.destination,
                  flight.date_of_departure,
                  flight.time_of_departure,
                  flight.date_of_arrival,
                  flight.time_of_arrival,
                  &flight.first_class_seat_avail,
                  &flight.first_class_seat_sold,
                  &flight.coach_seat_avail,
                  &flight.coach_seat_sold) != EOF)
    {
        printf("%-8s %-25s %-25s %-12s %-10s %-12s %-10s %-10d %-10d %-10d %-10d\n",
               flight.flight_number,
               flight.city_departure,
               flight.destination,
               flight.date_of_departure,
               flight.time_of_departure,
               flight.date_of_arrival,
               flight.time_of_arrival,
               flight.first_class_seat_avail,
               flight.first_class_seat_sold,
               flight.coach_seat_avail,
               flight.coach_seat_sold);
    }

    fclose(fp);
}
