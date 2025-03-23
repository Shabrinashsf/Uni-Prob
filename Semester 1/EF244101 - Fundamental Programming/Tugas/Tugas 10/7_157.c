#include <stdio.h>
#include <string.h>

typedef struct
{
    char flight_number[6];
    char city_departure[50];
    char destination[50];
    char date_departure[9];
    char time_departure[9];
    char date_arrival[9];
    char time_arrival[9];
    int first_class_seats_avail;
    int first_class_seats_sold;
    int coach_seats_avail;
    int coach_seats_sold;
} airline;

// Function prototypes
void create_flight(const char *filename);
void delete_flight(const char *filename, const char *flight_number);
void update_flight(const char *filename, const char *flight_number);
void make_reservation(const char *filename, const char *flight_number, int first_class, int coach);
void cancel_reservation(const char *filename, const char *flight_number, int first_class, int coach);
void display_flights(const char *filename);

int main()
{
    const char *filename = "airline_database.bin";
    int choice;

    do
    {
        printf("\n--- Airline Reservation System ---\n");
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

        char flight_number[6];
        int first_class, coach;

        switch (choice)
        {
        case 1:
            create_flight(filename);
            break;
        case 2:
            printf("Enter flight number to delete: ");
            scanf("%s", flight_number);
            delete_flight(filename, flight_number);
            break;
        case 3:
            printf("Enter flight number to update: ");
            scanf("%s", flight_number);
            update_flight(filename, flight_number);
            break;
        case 4:
            printf("Enter flight number to make a reservation: ");
            scanf("%s", flight_number);
            printf("Enter number of first-class seats to reserve: ");
            scanf("%d", &first_class);
            printf("Enter number of coach seats to reserve: ");
            scanf("%d", &coach);
            make_reservation(filename, flight_number, first_class, coach);
            break;
        case 5:
            printf("Enter flight number to cancel reservation: ");
            scanf("%s", flight_number);
            printf("Enter number of first-class seats to cancel: ");
            scanf("%d", &first_class);
            printf("Enter number of coach seats to cancel: ");
            scanf("%d", &coach);
            cancel_reservation(filename, flight_number, first_class, coach);
            break;
        case 6:
            display_flights(filename);
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

void create_flight(const char *filename)
{
    FILE *file = fopen(filename, "ab");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    airline flight;
    printf("Enter flight number: ");
    scanf("%s", flight.flight_number);
    printf("Enter departure city: ");
    scanf(" %[^\n]", flight.city_departure);
    printf("Enter destination city: ");
    scanf(" %[^\n]", flight.destination);
    printf("Enter departure date (YYYYMMDD): ");
    scanf("%s", flight.date_departure);
    printf("Enter departure time (HHMMSS): ");
    scanf("%s", flight.time_departure);
    printf("Enter arrival date (YYYYMMDD): ");
    scanf("%s", flight.date_arrival);
    printf("Enter arrival time (HHMMSS): ");
    scanf("%s", flight.time_arrival);
    printf("Enter number of first-class seats available: ");
    scanf("%d", &flight.first_class_seats_avail);
    flight.first_class_seats_sold = 0;
    printf("Enter number of coach seats available: ");
    scanf("%d", &flight.coach_seats_avail);
    flight.coach_seats_sold = 0;

    fwrite(&flight, sizeof(airline), 1, file);
    fclose(file);

    printf("Flight added successfully.\n");
}

void delete_flight(const char *filename, const char *flight_number)
{
    FILE *file = fopen(filename, "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (!file || !temp)
    {
        printf("Error opening file.\n");
        return;
    }

    airline flight;
    int found = 0;

    while (fread(&flight, sizeof(airline), 1, file))
    {
        if (strcmp(flight.flight_number, flight_number) != 0)
        {
            fwrite(&flight, sizeof(airline), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.bin", filename);

    if (found)
    {
        printf("Flight deleted successfully.\n");
    }
    else
    {
        printf("Flight not found.\n");
    }
}

void update_flight(const char *filename, const char *flight_number)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    airline flight;
    int found = 0;

    while (fread(&flight, sizeof(airline), 1, file))
    {
        if (strcmp(flight.flight_number, flight_number) == 0)
        {
            printf("Enter new departure city: ");
            scanf(" %[^\n]", flight.city_departure);
            printf("Enter new destination city: ");
            scanf(" %[^\n]", flight.destination);
            printf("Enter new departure date (YYYYMMDD): ");
            scanf("%s", flight.date_departure);
            printf("Enter new departure time (HHMMSS): ");
            scanf("%s", flight.time_departure);
            printf("Enter new arrival date (YYYYMMDD): ");
            scanf("%s", flight.date_arrival);
            printf("Enter new arrival time (HHMMSS): ");
            scanf("%s", flight.time_arrival);
            printf("Enter new number of first-class seats available: ");
            scanf("%d", &flight.first_class_seats_avail);
            printf("Enter new number of coach seats available: ");
            scanf("%d", &flight.coach_seats_avail);

            fseek(file, -(long)sizeof(airline), SEEK_CUR);
            fwrite(&flight, sizeof(airline), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("Flight updated successfully.\n");
    }
    else
    {
        printf("Flight not found.\n");
    }
}

void make_reservation(const char *filename, const char *flight_number, int first_class, int coach)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    airline flight;
    int found = 0;

    while (fread(&flight, sizeof(airline), 1, file))
    {
        if (strcmp(flight.flight_number, flight_number) == 0)
        {
            if (flight.first_class_seats_avail >= first_class && flight.coach_seats_avail >= coach)
            {
                flight.first_class_seats_avail -= first_class;
                flight.first_class_seats_sold += first_class;
                flight.coach_seats_avail -= coach;
                flight.coach_seats_sold += coach;

                fseek(file, -(long)sizeof(airline), SEEK_CUR);
                fwrite(&flight, sizeof(airline), 1, file);

                printf("Reservation made successfully.\n");
            }
            else
            {
                printf("Not enough seats available.\n");
            }
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Flight not found.\n");
    }
}

void cancel_reservation(const char *filename, const char *flight_number, int first_class, int coach)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    airline flight;
    int found = 0;

    while (fread(&flight, sizeof(airline), 1, file))
    {
        if (strcmp(flight.flight_number, flight_number) == 0)
        {
            if (flight.first_class_seats_sold >= first_class && flight.coach_seats_sold >= coach)
            {
                flight.first_class_seats_avail += first_class;
                flight.first_class_seats_sold -= first_class;
                flight.coach_seats_avail += coach;
                flight.coach_seats_sold -= coach;

                fseek(file, -(long)sizeof(airline), SEEK_CUR);
                fwrite(&flight, sizeof(airline), 1, file);

                printf("Reservation canceled successfully.\n");
            }
            else
            {
                printf("Not enough reserved seats to cancel.\n");
            }
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Flight not found.\n");
    }
}

void display_flights(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    airline flight;

    printf("\n--- Flight List ---\n");
    while (fread(&flight, sizeof(airline), 1, file))
    {
        printf("\nFlight Number: %s\n", flight.flight_number);
        printf("Departure City: %s\n", flight.city_departure);
        printf("Destination: %s\n", flight.destination);
        printf("Departure Date: %s\n", flight.date_departure);
        printf("Departure Time: %s\n", flight.time_departure);
        printf("Arrival Date: %s\n", flight.date_arrival);
        printf("Arrival Time: %s\n", flight.time_arrival);
        printf("First-Class Seats (Available/Sold): %d/%d\n", flight.first_class_seats_avail, flight.first_class_seats_sold);
        printf("Coach Seats (Available/Sold): %d/%d\n", flight.coach_seats_avail, flight.coach_seats_sold);
    }

    fclose(file);
}