#include <stdio.h>
#include <string.h>

typedef struct
{
    char nama[20];
    int mat;
    int ipa;
    int indo;
    int eng;
} UN;

int main()
{
    int data;
    int n;
    scanf("%d", &data);
    UN siswa[data];

    for (int i = 0; i < data; i++)
    {
        scanf("%s", siswa[i].nama);
        scanf("%d", siswa[i].mat);
        scanf("%d", siswa[i].ipa);
        scanf("%d", siswa[i].indo);
        scanf("%d", siswa[i].eng);
    }

    scanf("%d", &n);
    char cariNama[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", cariNama[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < data; j++)
        {
            if (strcmp(cariNama[i], siswa[j].nama) == 0)
            {
                printf("Nilai %s\n", cariNama[i]);
                printf("Matematika\t: %d", siswa[j].mat);
                printf("IPA\t: %d", siswa[j].ipa);
                printf("Bahasa Indonesia\t: %d", siswa[j].indo);
                printf("Bahasa Inggris\t: %d", siswa[j].eng);
            }
            else
            {
                printf("Nilai %s tidak ditemukan\n", cariNama[i]);
            }
        }
    }
}