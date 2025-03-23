#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_SIZE 70
#define MAX_SITES 10

typedef struct
{
    char site_id_num[5];
    int day_of_month;
    int wind_speed;
    int temperature;
} measured_data_t;

int main()
{
    measured_data_t data[MAX_SIZE];
    FILE *file = fopen("data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int count = 0;
    while (count < MAX_SIZE && fscanf(file, "%4s %d %d %d", data[count].site_id_num, &data[count].day_of_month, &data[count].wind_speed, &data[count].temperature) == 4)
    {
        count += 1;
    }
    fclose(file);

    int actual_size = count / 7;
    int max_variation = 0;
    char max_sites[MAX_SITES][5];
    int max_site_count = 0;
    float max_avg = 0.0;
    char max_site_avg[5];

    for (int i = 0; i < actual_size; i++)
    {
        int max_temp = INT_MIN;
        int min_temp = INT_MAX;
        int wind_sum = 0;

        for (int j = 0; j < 7; j++)
        {
            int idx = i * 7 + j;
            if (data[idx].temperature > max_temp)
                max_temp = data[idx].temperature;
            if (data[idx].temperature < min_temp)
                min_temp = data[idx].temperature;
            wind_sum += data[idx].wind_speed;
        }

        int variation = max_temp - min_temp;
        if (variation > max_variation)
        {
            max_variation = variation;
            max_site_count = 0;
            snprintf(max_sites[max_site_count], 5, "%s", data[i * 7].site_id_num);
            max_site_count++;
        }
        else if (variation == max_variation)
        {
            snprintf(max_sites[max_site_count], 5, "%s", data[i * 7].site_id_num);
            max_site_count++;
        }

        float avg_wind_speed = wind_sum / 7.0;
        if (avg_wind_speed > max_avg)
        {
            max_avg = avg_wind_speed;
            snprintf(max_site_avg, 5, "%s", data[i * 7].site_id_num);
        }
    }

    printf("Sites with the greatest variation in temperature (%d):\n", max_variation);
    for (int i = 0; i < max_site_count; i++)
    {
        printf("- %s\n", max_sites[i]);
    }

    printf("Site with the highest average wind speed: %s (%.2f)\n", max_site_avg, max_avg);

    return 0;
}
