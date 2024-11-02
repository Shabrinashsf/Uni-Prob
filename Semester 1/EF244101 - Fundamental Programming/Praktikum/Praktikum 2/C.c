// Write by Shabrina Amalia Safaana

#include <stdio.h>
// sans & grillby
// udh ac
int main()
{
    int t;
    scanf("%d", &t);
    int harga[t + 1]; // karena disini saya make arraynya mulai dari indeks 0
    for (int i = 1; i <= t; i++)
    {
        scanf("%d", &harga[i]);
    }

    // untuk menghitung harga maksimal dalam satu kali inputan
    int max = 0;
    for (int i = 1; i <= t; i++)
    {
        if (harga[i] > max)
        {
            max = harga[i];
        }
    }

    // k is for kemunculan
    int k[max + 1];
    for (int i = 0; i < max + 1; i++)
    {
        k[i] = 0;
    }

    // jika menemukan harga, masukkan harga tersebut ke indeks array k sesuai dengan harganya, jika harga 7 maka masukkan ke array indedks 7
    for (int i = 1; i <= t; i++)
    {
        for (int j = 1; j < max + 1; j++)
        {
            if (harga[i] == j)
            {
                k[j] += 1;
            }
        }
    }

    // untuk menghitung banyak maksimal kemunculan
    int maxK = 0;
    int modus; // nominal harganya / indeks array yg muncul paling banyak
    for (int i = 1; i < max + 1; i++)
    {
        if (k[i] > maxK)
        {
            maxK = k[i]; // untuk tau berapa banyak harga itu muncul dalam satu kali input
            modus = i;
        }
        if (k[i] == maxK)
        {
            if (i > modus)
            {
                modus = i;
            }
        }
    }

    printf("Modus: %d\n", modus);

    // untuk menghitung apakah modusnya prima atau engga
    int prime = 1;
    for (int i = 2; i < modus; i++)
    {
        if (modus % i == 0)
        {
            i = modus; // agar setelah menemukan bahwa modus bisa habis dibagi i yang selain 1 dan dirinya sendiri, maska loop gak akan ngecek lagi
            prime = 0;
        }
    }

    if (modus == 2 || modus == 3)
    {
        printf("Wah, modusnya prima nihh.");
    }
    else if (prime != 0)
    {
        printf("Wah, modusnya prima nihh.");
    }
    else
    {
        printf("Yah, modusnya gak prima.");
    }
}
