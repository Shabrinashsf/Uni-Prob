#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    // note untuk diri sendiri karena suka lupa
    long long n, m, f, i, k, jumlahBit, bitN, bitM;
    scanf("%lld %lld %lld", &n, &m, &f);
    m += 1; // karena nanti maunya n xor k >= m + 1, ini batas minimalnya

    jumlahBit = log2((n >= m) ? n : m); // ambil yg lebih besar agar loopingnya nanti bisa include yg besar, sedangkan yg kecil menyesuaikan

    for (i = jumlahBit, k = 0; i >= 0; i--) // karena berakhir di sama dengan 0 maka jumlah bit nanti p + 1, jumlah bit ini untuk sebagai batasan loop
    {
        bitN = (n & (1LL << i));
        bitM = (m & (1LL << i));

        // ketika nilai n = m maka gak ngubah nilai k, kembali loop

        if (!bitN && bitM)
        { // ketika n < m maka ngubah nilai k nya
            k += (1LL << i);
        }
        else if (bitN && !bitM)
        { // ketika n > m maka langsung keluar loop
            break;
        }
    }

    if (k <= f)
    {
        printf("HAHAHA, I CAN SAVE THE WORLD\n");
    }
    else
    {
        printf("OH NOOO, I FAILED\n");
    }
}