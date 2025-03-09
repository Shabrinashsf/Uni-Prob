#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dd, mm, yyyy;
} tanggal;

typedef struct
{
    char provinsi[20];
    char kota[20];
    char NIK[17];
    char nama[50];
    char tempatLahir[50];
    tanggal tanggalLahir;
    char jenisKelamin[10];
    char golDarah;
    char alamat[50];
    char rt[4];
    char rw[4];
    char kelurahan[50];
    char kecamatan[50];
    char agama[10];
    char statusPerkawinan[12];
    char pekerjaan[50];
    char kewarganegaraan[4];
    tanggal tanggalBerlaku;
    tanggal tanggalDibuat;
} ktp;

// Helper
void clear_screen();
void input_nik(ktp data[100], int id);
void input_tanggal(ktp data[100], int id, int versi);

// Function
void add_data(ktp data[100], int *id);
void search_data(ktp data[100], int *id, char findNIK[17]);
void delete_data(ktp data[100], int *id, char findNIK[17]);
void display_all_data(ktp data[100], int *id);
void display_data(ktp data[100], int i);

void main()
{
    ktp data[100];
    int id = 0;
    int opsi = 0;
    char findNIK[17];

    do
    {
        printf("Silahkan pilih nomor\n");
        printf("1. Add data\n");
        printf("2. Search data by NIK\n");
        printf("3. Display all data\n");
        printf("4. Delete data by NIK\n");
        printf("5. Exit\n");
        printf("Masukkan opsi yang anda ingin jalankan: ");
        scanf("%d", &opsi);
        getchar();
        clear_screen();

        switch (opsi)
        {
        case 1:
            add_data(data, &id);
            break;
        case 2:
            printf("Masukkan NIK yang ingin anda cari: ");
            scanf("%16s", findNIK);
            search_data(data, &id, findNIK);
            break;
        case 3:
            display_all_data(data, &id);
            break;
        case 4:
            printf("Masukkan NIK yang ingin anda hapus: ");
            scanf("%16s", findNIK);
            delete_data(data, &id, findNIK);
            break;
        case 5:
            printf("Terima kasih telah menggunakan program!\n");
            return;
        default:
            printf("Pilihan tidak sesuai\n");
            printf("Mohon masukkan opsi Yang Sesuai\n");
            clear_screen();
        }
    } while (1);
}

void add_data(ktp data[100], int *id)
{
    char input;

    do
    {
        input_nik(data, *id);
        printf("Masukkan NIK: %s\n", data[*id].NIK);
        printf("Masukkan nama: ");
        scanf(" %[^\n]", data[*id].nama);
        printf("Masukkan provinsi: ");
        scanf(" %[^\n]", data[*id].provinsi);
        printf("Masukkan kota: ");
        scanf(" %[^\n]", data[*id].kota);
        printf("Masukkan tempat lahir: ");
        scanf(" %[^\n]", data[*id].tempatLahir);
        printf("Masukkan tanggal lahir (dd mm yyyy): ");
        scanf("%d %d %d", &data[*id].tanggalLahir.dd, &data[*id].tanggalLahir.mm, &data[*id].tanggalLahir.yyyy);
        printf("Masukkan jenis kelamin: ");
        scanf(" %[^\n]", data[*id].jenisKelamin);
        printf("Masukkan golongan darah: ");
        scanf(" %c", &data[*id].golDarah);
        printf("Masukkan alamat tinggal: ");
        scanf(" %[^\n]", data[*id].alamat);
        printf("Masukkan RT (ex: 001, isi 0 jika tidak ada): ");
        scanf("%s", data[*id].rt);
        printf("Masukkan RW (ex: 001, isi 0 jika tidak ada): ");
        scanf("%s", data[*id].rw);
        printf("Masukkan kelurahan: ");
        scanf(" %[^\n]", data[*id].kelurahan);
        printf("Masukkan kecamatan: ");
        scanf(" %[^\n]", data[*id].kecamatan);
        printf("Masukkan agama: ");
        scanf(" %[^\n]", data[*id].agama);
        printf("Masukkan status perkawinan: ");
        scanf(" %[^\n]", data[*id].statusPerkawinan);
        printf("Masukkan pekerjaan: ");
        scanf(" %[^\n]", data[*id].pekerjaan);
        printf("Masukkan kewarganegaraan: ");
        scanf(" %[^\n]", data[*id].kewarganegaraan);
        printf("Masukkan berlaku (dd mm yyyy): ");
        scanf("%d %d %d", &data[*id].tanggalBerlaku.dd, &data[*id].tanggalBerlaku.mm, &data[*id].tanggalBerlaku.yyyy);
        printf("Masukkan tanggal dibuat (dd mm yyyy): ");
        scanf("%d %d %d", &data[*id].tanggalDibuat.dd, &data[*id].tanggalDibuat.mm, &data[*id].tanggalDibuat.yyyy);
        clear_screen();

        printf("Data berhasil ditambahkan!\n");
        printf("Ingin memasukkan data lagi? (Y/N): ");
        scanf("%c", &input);
        clear_screen();

        (*id)++;
    } while (input == 'Y' || input == 'y');
}

void search_data(ktp data[100], int *id, char findNIK[17])
{
    if (*id == 0)
    {
        printf("Belum ada data yang diinput!\n");
    }
    else
    {
        for (int i = 0; i < *id; i++)
        {
            if (strcmp(data[i].NIK, findNIK) == 0)
            {
                display_data(data, i);
                break;
            }
        }
    }
}

void display_all_data(ktp data[100], int *id)
{
    if (*id == 0)
    {
        printf("Belum ada data yang diinput!\n");
    }
    else
    {
        for (int i = 0; i < *id; i++)
        {
            display_data(data, i);
        }
    }
}

void delete_data(ktp data[100], int *id, char findNIK[17])
{
    if (*id == 0)
    {
        printf("Belum ada data yang diinput!\n");
        return;
    }

    int exist = 0;
    for (int i = 0; i < *id; i++)
    {
        if (strcmp(data[i].NIK, findNIK) == 0)
        {
            exist = 1;
            for (int j = i; j < *id - 1; j++)
            {
                data[j] = data[j + 1];
            }
            (*id)--;
            printf("Data berhasil dihapus!\n");
            break;
        }
    }
    if (exist == 0)
    {
        printf("Data tidak ada!\n");
    }
}

void display_data(ktp data[100], int i)
{
    printf("Provinsi: %s\n", data[i].provinsi);
    printf("Kota: %s\n", data[i].kota);
    printf("NIK: %s\n", data[i].NIK);
    printf("Tempat lahir: %s\n", data[i].tempatLahir);
    printf("Tanggal lahir: %d %d %d\n", data[i].tanggalLahir.dd, data[i].tanggalLahir.mm, data[i].tanggalLahir.yyyy);
    printf("Jenis kelamin: %s\n", data[i].jenisKelamin);
    printf("Golongan darah: %c\n", data[i].golDarah);
    printf("Alamat: %s\n", data[i].alamat);
    printf("RT: %s\n", data[i].rt);
    printf("RW: %s\n", data[i].rw);
    printf("Kelurahan: %s\n", data[i].kelurahan);
    printf("Kecamatan: %s\n", data[i].kecamatan);
    printf("Agama: %s\n", data[i].agama);
    printf("Status Perkawinan: %s\n", data[i].statusPerkawinan);
    printf("Pekerjaan: %s\n", data[i].pekerjaan);
    printf("Kewarganegaraan: %s\n", data[i].kewarganegaraan);
    printf("Tanggal berlaku: %d %d %d\n", data[i].tanggalBerlaku.dd, data[i].tanggalBerlaku.mm, data[i].tanggalBerlaku.yyyy);
    printf("Tanggal dibuat: %d %d %d\n", data[i].tanggalDibuat.dd, data[i].tanggalDibuat.mm, data[i].tanggalDibuat.yyyy);
}

void clear_screen()
{
    printf("Press enter to continue.....\n");
    getchar();
    system("cls");
}

void input_nik(ktp data[100], int id)
{
    char tempNIK[17];
    while (1)
    {
        printf("Masukkan nomor NIK (16 digit): ");
        scanf("%16s", tempNIK);
        clear_screen();

        if (strlen(tempNIK) != 16)
        {
            printf("Masukkan dengan NIK yang benar (16 karakter)!\n");
            clear_screen();
        }
        else
        {
            for (int i = 0; i <= id; i++)
            {
                if (strcmp(data[i].NIK, tempNIK) == 0)
                {
                    printf("NIK yang diinput telah terdaftar, masukkan NIK lagi!\n");
                    clear_screen();
                    break;
                }
                else if (i == id)
                {
                    strcpy(data[id].NIK, tempNIK);
                    printf("NIK berhasil ditambahkan!\n");
                    clear_screen();
                    return;
                }
            }
        }
    }
}

/*
void input_tanggal(ktp data[100], int id, int versi)
{
    int dd, mm, yyyy;
    int true = 0;
    while (1)
    {
        printf("Masukkan tanggal lahir (ex: dd mm yyyy): ");
        scanf("%d %d %d", &dd, &mm, &yyyy);
        clear_screen();

        if (dd > 0 && dd <= 31)
        {
            true ++;
        }
        if (mm > 0 && mm <= 12)
        {
            true ++;
        }
        if (yyyy > 0)
        {
            true ++;
        }
        if (true == 3)
        {
            if (versi == 1)
            { // tanggal lahir
                data[id].tanggalLahir.dd = dd;
                data[id].tanggalLahir.mm = mm;
                data[id].tanggalLahir.yyyy = yyyy;
                printf("Tanggal lahir berhasil ditambahkan");
                clear_screen();
                break;
            }
            else if (versi == 2)
            { // tanggal berlaku
                data[id].tanggalBerlaku.dd = dd;
                data[id].tanggalBerlaku.mm = mm;
                data[id].tanggalBerlaku.yyyy = yyyy;
                printf("Tanggal berlaku berhasil ditambahkan");
                clear_screen();
                break;
            }
            else if (versi == 3)
            { // tanggal dibuat
                data[id].tanggalDibuat.dd = dd;
                data[id].tanggalDibuat.mm = mm;
                data[id].tanggalDibuat.yyyy = yyyy;
                printf("Tanggal dibuat berhasil ditambahkan");
                clear_screen();
                return;
            }
        }
    }
}
*/