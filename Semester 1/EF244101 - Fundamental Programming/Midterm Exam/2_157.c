#include <stdio.h>
#include <string.h>

// Shabrina Amalia Safaana 5025241157

int main()
{
    printf("Note: program ini akan menghitung karakter titik\n");
    printf("Note: Anda akan keluar dari program apabila anda hanya memasukkan karakter '.'\n");
    printf("\n");
    while (1)
    {
        int jumlahSpace = 0;
        printf("Masukkan pesan ingin anda kirim\n");
        char pesan[200];
        scanf("%[^\n]%*c", pesan);
        if (pesan[0] == '.')
        {
            printf("Anda telah keluar dari program");
            break;
        }
        int size = strlen(pesan);

        int jumlah = 0;
        for (int i = 0; i < size; i++)
        {
            if (pesan[i] == ' ')
            {
                jumlahSpace++;
            }
            else if (pesan[i] != ' ')
            {
                jumlah += pesan[i];
            }
        }

        int checksum = jumlah % 64;
        checksum = checksum + (jumlahSpace * ' ');
        printf("Karakter untuk nilai dari checksum adalah: %c\n", checksum);
        printf("\n");
    }
}