#include <stdio.h>
#include <string.h>

typedef struct
{
    char pemain[20];
    int assist;
    int gol;
    int keypass;
    int dribble;
    double motm;
    char nama_assist[20];
} data;

typedef struct
{
    char nama_assist[20];
    char nama_gol[20];
    int assist_gol;
} tambahan1;

typedef struct
{
    char pemain[20];
    int keypass;
    int dribble;
} tambahan;

int main()
{
    int n;
    scanf("%d", &n);
    data person[n];
    tambahan stat[n];
    tambahan1 temp[n];

    for (int i = 0; i < n; i++)
    {
        person[i].assist = 0;
        person[i].gol = 0;
        person[i].keypass = 0;
        person[i].dribble = 0;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%s", person[i].pemain);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %d", temp[i].nama_assist, temp[i].nama_gol, &temp[i].assist_gol);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%s %d %d", stat[i].pemain, &stat[i].keypass, &stat[i].dribble);
    }

    // masukan jumlah gol dan jumlah assist +++ masukan jumlah key dan dribble
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strcmp(temp[i].nama_assist, person[j].pemain) == 0)
            {
                person[j].assist += temp[i].assist_gol;
                strcpy(person[j].nama_assist, temp[i].nama_gol);
            }
            if (strcmp(temp[i].nama_gol, person[j].pemain) == 0)
            {
                person[j].gol += temp[i].assist_gol;
            }
            if (strcmp(stat[i].pemain, person[j].pemain) == 0)
            {
                person[j].keypass += stat[i].keypass;
                person[j].dribble += stat[i].dribble;
            }
        }
    }

    double max = 0.0;
    int index_motm;
    for (int i = 0; i < n; i++)
    {
        person[i].motm = (3.0 * (double)person[i].gol) + (2.0 * (double)person[i].assist) + (double)person[i].keypass + (0.2 * (double)person[i].dribble);
        if (person[i].motm > max)
        {
            max = person[i].motm;
            index_motm = i;
        }
    }

    int t;
    scanf("%d", &t);
    char perintah[t][6];

    for (int i = 0; i < t; i++)
    {
        scanf("%s", perintah[i]);
    }

    for (int i = 0; i < t; i++)
    {
        if (strcmp(perintah[i], "TABLE") == 0)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%s | Goals: %d | Assists: %d | Assist To: %s\n", person[j].pemain, person[j].gol, person[j].assist, person[j].nama_assist);
            }
        }
        else if (strcmp(perintah[i], "MOTM") == 0)
        {
            printf("Man of the Match: %s\n", person[index_motm].pemain);
        }
    }
}