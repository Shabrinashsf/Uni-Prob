#include <stdio.h>

// Shabrina Amalia Safaana 5025241157

void get_grid(int arr[][4])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void display_grid(int arr[][4])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int power_ok(int arr[][4])
{
    int menyala = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == 1)
            {
                menyala++;
            }
        }
    }
    if (menyala == 12)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int where_of(int arr[][4], int *kondisiJaringan, int x[][4], int y[][4])
{
    if (*kondisiJaringan == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (arr[i][j] == 0)
                {
                    x[i][j] = i;
                    y[i][j] = j;
                }
            }
        }

        printf("Daya mati di sektor: ");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (x[i][j] != 100 && y[i][j] != 100)
                {
                    printf("(%d,%d) ", x[i][j], y[i][j]);
                }
            }
        }
        printf("\n");
    }
    else
    {
        printf("Daya menyala di seluruh jaringan.\n");
    }
}

int main()
{
    int sektorX[3][4];
    int sektorY[3][4];
    int listrik[3][4];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sektorX[i][j] = 100;
            sektorY[i][j] = 100;
        }
    }
    get_grid(listrik);
    int kondisi = power_ok(listrik);
    where_of(listrik, &kondisi, sektorX, sektorY);
    display_grid(listrik);
}