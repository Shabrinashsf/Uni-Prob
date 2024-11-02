#include <stdio.h>
// picky eater
int main()
{
    int n;
    int temp;
    int kurang;
    scanf("%d", &n);
    int id[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &id[i]);
    }

    // k is for kemunculan
    int k[11];
    for (int i = 0; i < 11; i++)
    {
        k[i] = 0;
    }

    if (n == 1)
    {
        printf("%d\n", id[1]);
        printf("0");
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (id[i] == j)
            {
                k[j] += 1;
            }
        }
    }

    // m is for max kemunculan
    int m = 0;
    int mayoritas;
    int id_sama = 0;
    for (int i = 1; i < 11; i++)
    {
        if (k[i] > m)
        {
            m = k[i];
            mayoritas = i;
            id_sama = 1;
        }
        else if (k[i] == m)
        {
            id_sama++;
        }
    }

    if (id_sama > 1)
    {
        printf("-1\n");
        return 0;
    }

    kurang = n - m;
    printf("%d\n", mayoritas);
    printf("%d", kurang);
}