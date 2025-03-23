#include <stdio.h>
#include <string.h>

/* arr[] ---> Input Array
   n ---> Ukuran array input
   r ---> Ukuran kombinasi yang akan dicetak
   index ---> Indeks saat ini di data[]
   data[] ---> Array sementara untuk menyimpan kombinasi saat ini
   i ---> Indeks elemen saat ini di arr[] */

void combinationUtil(char arr[], int n, int r, int index, char data[], int i);

// Fungsi untuk mengurutkan array (bubble sort)
void sortArray(char arr[], int n)
{
    int temp, i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Fungsi utama untuk mencetak semua kombinasi unik
void printCombination(char arr[], int n, int r)
{
    // Array sementara untuk menyimpan kombinasi
    char data[r];

    // Urutkan array untuk menangani duplikat
    sortArray(arr, n);

    // Cetak semua kombinasi menggunakan array sementara 'data[]'
    combinationUtil(arr, n, r, 0, data, 0);
}

void combinationUtil(char arr[], int n, int r, int index, char data[], int i)
{
    if (index == r && r == 1)
    {
        for (int j = 0; j < r; j++)
        {
            printf("{%c}", data[j]);
        }
        printf("\n");
        return;
    }

    if (index == r && r == 2 || index == r && r == 3)
    {
        printf("{");
        for (int j = 0; j < r; j++)
        {
            printf("%c", data[j]);
            if (j < r - 1)
            {
                printf(", ");
            }
        }
        printf("}\n");
        return;
    }

    // Jika sudah tidak ada elemen yang tersisa untuk dimasukkan
    if (i >= n)
        return;

    // Elemen saat ini dimasukkan, lanjutkan untuk menambah elemen berikutnya
    data[index] = arr[i];
    combinationUtil(arr, n, r, index + 1, data, i + 1);

    // Menghindari duplikat: jika elemen yang sama berturut-turut, lewati elemen yang duplikat
    while (arr[i] == arr[i + 1] && i + 1 < n)
    {
        i++;
    }

    // Elemen saat ini dikeluarkan, lanjutkan ke elemen berikutnya
    combinationUtil(arr, n, r, index, data, i + 1);
}

int main()
{
    char input[100];
    printf("Input the letter:\n");
    scanf("%s", input);
    int len = strlen(input);
    char arr[len];
    strcpy(arr, input);
    int n = sizeof(arr) / sizeof(arr[0]);

    // Panggil fungsi untuk mencetak kombinasi
    printf("one-element subsets\n");
    printf("(\"%s\")\n", input);
    printCombination(arr, n, 1);
    printf("\n");

    printf("two-element subsets\n");
    printf("(\"%s\")\n", input);
    printCombination(arr, n, 2);
    printf("\n");

    printf("three-element subsets\n");
    printf("(\"%s\")\n", input);
    printCombination(arr, n, 3);
    printf("\n");
}