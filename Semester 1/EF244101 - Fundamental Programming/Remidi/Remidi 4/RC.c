#include <stdio.h>
#include <string.h>

typedef struct
{
    char nama[101];
    char ip[101];
    char uuid[101];
} player;

typedef struct
{
    char name[101];
} allow;

int main()
{
    int n;
    scanf("%d", &n);

    player pemain[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %s", pemain[i].nama, pemain[i].ip, pemain[i].uuid);
    }

    int m;
    scanf("%d", &m);
    allow user[m];

    for (int i = 0; i < m; i++)
    {
        scanf("%s", user[i].name);
    }

    for (int i = 0; i < m; i++)
    {
        int found = 0;
        for (int j = 0; j < n; j++)
        {
            if (strcmp(user[i].name, pemain[j].nama) == 0)
            {
                found = 1;
                printf("asyik %s-%s diperbolehkan bermain\n", pemain[j].uuid, pemain[j].nama);
                break;
            }
        }
        if (!found)
        {
            printf("hmm, kayaknya ada yang salah dengan datamu\n");
        }
    }

    return 0;
}
