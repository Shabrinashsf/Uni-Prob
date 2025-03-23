#include <stdio.h>

void fget_point_mass(int *n, int loc[][3], int beban[])
{
    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &loc[i][j]);
        }
        scanf("%d", &beban[i]);
    }
}

void center_grav(int loc[][3], int mass[], int *n, float center[])
{
    int m = 0;
    for (int i = 0; i < *n; i++)
    {
        m += mass[i];
    }

    float tempX = 0.0;
    float tempY = 0.0;
    float tempZ = 0.0;
    for (int i = 0; i < *n; i++)
    {
        tempX = tempX + ((float)mass[i] * (float)loc[i][0]);
        tempY = tempY + ((float)mass[i] * (float)loc[i][1]);
        tempZ = tempZ + ((float)mass[i] * (float)loc[i][2]);
    }

    center[0] = tempX / (float)m;
    center[1] = tempY / (float)m;
    center[2] = tempZ / (float)m;
}

void fwrite_point_mass(int *n, int loc[][3], int beban[], float center[])
{
    printf("location %2c", ' ');
    for (int i = 0; i < *n; i++)
    {
        printf("(");
        for (int j = 0; j < 3; j++)
        {
            printf("%d", loc[i][j]);
            if (j == 0 || j == 1)
                printf(", ");
            else
                printf(")");
        }
        printf("\n");
        printf("%11c", ' ');
    }

    printf("\n");

    printf("mass %7c", ' ');
    for (int i = 0; i < *n; i++)
    {
        printf("%dg\n", beban[i]);
        printf("%12c", ' ');
    }

    printf("\n");

    printf("n %9c %d\n", ' ', *n);

    printf("Center Of Gravity: %.2f, %.2f, %.2f", center[0], center[1], center[2]);
}

int main()
{
    // batas nilai n adalah 3 sampai 10
    int n;
    printf("Enter n value between 3 and 10:\n");
    scanf("%d", &n);
    int mass[n];
    int location[n][3];
    float centerGravity[3];

    fget_point_mass(&n, location, mass);
    if (n > 10 && n < 3)
    {
        printf("Your n value is not in range 3 to 10, please enter n value in range 3 to 10!");
        return 0;
    }
    center_grav(location, mass, &n, centerGravity);
    fwrite_point_mass(&n, location, mass, centerGravity);
}