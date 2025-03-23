#include <stdio.h>
#include <stdlib.h>

// Fungsi untuk mengecek apakah posisi (x, y) berada dalam batas dan berisi 1
int aman(int **arr, int x, int y, int baris, int kolom)
{
    return (x >= 0 && x < baris && y >= 0 && y < kolom && arr[x][y] == 1);
}

void blob_check(int **arr, int x, int y, int baris, int kolom)
{
    // Tandai sel (x, y) sebagai sudah dikunjungi dengan mengganti nilainya menjadi 0
    arr[x][y] = 0;

    // Cek ke atas
    if (aman(arr, x - 1, y, baris, kolom))
    {
        blob_check(arr, x - 1, y, baris, kolom);
    }
    // Cek ke bawah
    if (aman(arr, x + 1, y, baris, kolom))
    {
        blob_check(arr, x + 1, y, baris, kolom);
    }
    // Cek ke kiri
    if (aman(arr, x, y - 1, baris, kolom))
    {
        blob_check(arr, x, y - 1, baris, kolom);
    }
    // Cek ke kanan
    if (aman(arr, x, y + 1, baris, kolom))
    {
        blob_check(arr, x, y + 1, baris, kolom);
    }
}

int check(int **arr, int baris, int kolom)
{
    int count = 0;

    for (int i = 0; i < baris; i++)
    {
        for (int j = 0; j < kolom; j++)
        {
            if (arr[i][j] == 1)
            {
                blob_check(arr, i, j, baris, kolom);
                count++;
            }
        }
    }
    return count;
}

int main()
{
    int baris, kolom;
    printf("Enter matrix size (rows columns):\n");
    scanf("%d %d", &baris, &kolom);

    // Alokasikan memori untuk matriks pixel
    int **pixel = (int **)malloc(baris * sizeof(int *));
    for (int i = 0; i < baris; i++)
    {
        pixel[i] = (int *)malloc(kolom * sizeof(int));
    }
    // hanya unutk nyimpen memori aja, bisa juga cuma pake int pixel[baris][kolom];

    printf("Input the pixels:\n");

    for (int i = 0; i < baris; i++)
    {
        for (int j = 0; j < kolom; j++)
        {
            scanf("%d", &pixel[i][j]);
        }
    }

    printf("Total blobs in the pictures: %d\n", check(pixel, baris, kolom));

    // Bebaskan memori
    for (int i = 0; i < baris; i++)
    {
        free(pixel[i]);
    }
    free(pixel);
}
