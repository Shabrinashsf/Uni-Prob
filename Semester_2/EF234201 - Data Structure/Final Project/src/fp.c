#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

#define data_file "../data/component.dat"
#define data_indeks "../data/index.dat"
#define data_maks 1000
#define nama_length 26
#define kode_length 7

typedef struct
{
    char kode[kode_length];
    char nama[nama_length];
    int stok;
    double harga;
} Barang;

typedef struct
{
    char kode[kode_length];
    long offset;
} Indeks;

Barang komponen;
Indeks komponen_indeks[data_maks];
int komponen_jumlah = 0;

int banding(const void *a, const void *b); // qsort wajib ini
void file_error(const char *nama_file);
void clearscreen();
void load_index();
void save_index();
void tambah();
void ubah();
void view_indeks();
void noindeks();
void hapus();
void keluar();
void menu();

int main()
{
    menu();
    return 0;
}

int banding(const void *a, const void *b)
{
    return strcmp(((Indeks *)a)->kode, ((Indeks *)b)->kode);
}

void file_error(const char *nama_file)
{
    printf("%s file error or not found\n", nama_file);
}

void clearscreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void load_index()
{
    FILE *index_count = fopen(data_indeks, "rb");
    if (index_count)
    {
        komponen_jumlah = 0;
        while (fread(&komponen_indeks[komponen_jumlah], sizeof(Indeks), 1, index_count))
        {
            komponen_jumlah++;
        }
        fclose(index_count);
    }
    else
    {
        file_error(data_indeks);
    }
}

void save_index()
{
    FILE *index_file = fopen(data_indeks, "wb");
    if (index_file)
    {
        for (int i = 0; i < komponen_jumlah; i++)
        {
            fwrite(&komponen_indeks[i], sizeof(Indeks), 1, index_file);
        }
        fclose(index_file);
    }
    else
    {
        file_error(data_indeks);
    }
}

void tambah()
{
    FILE *fdat = fopen(data_file, "ab");
    if (!fdat)
    {
        if (!fdat)
            file_error(data_file);
        return;
    }

    Barang component;
    Indeks index;
    printf("Code: ");
    scanf("%s", component.kode);
    getchar();
    printf("Component name: ");
    fgets(component.nama, nama_length, stdin);
    printf("Stock: ");
    scanf("%d", &component.stok);
    printf("Price: ");
    scanf("%lf", &component.harga);
    component.nama[strcspn(component.nama, "\n")] = '\0'; // \n -> \0
    int len = strlen(component.nama);
    for (int i = len; i < nama_length - 1; i++)
    {
        component.nama[i] = ' ';
    }
    component.nama[nama_length - 1] = '\0';

    fseek(fdat, 0, SEEK_END);
    long pos_end = ftell(fdat);
    fwrite(&component, sizeof(Barang), 1, fdat);
    load_index();
    strcpy(index.kode, component.kode);
    index.offset = pos_end;
    komponen_indeks[komponen_jumlah++] = index;
    save_index();

    fclose(fdat);
    printf("Data added\n");
}

void ubah()
{
    char cari[kode_length];
    printf("Enter code to modify: ");
    scanf("%s", cari);
    load_index();
    FILE *fdat = fopen(data_file, "rb+");
    if (!fdat)
    {
        file_error(data_file);
        return;
    }

    for (int i = 0; i < komponen_jumlah; i++)
    {
        if (strcmp(komponen_indeks[i].kode, cari) == 0)
        {
            fseek(fdat, komponen_indeks[i].offset, SEEK_SET);
            fread(&komponen, sizeof(Barang), 1, fdat);

            printf("Old data\nName: %s\nStock: %d\nPrice: %.2f\n", komponen.nama, komponen.stok, komponen.harga);
            getchar();
            printf("New data\n");
            printf("Component name: ");
            fgets(komponen.nama, nama_length, stdin);
            printf("Stock: ");
            scanf("%d", &komponen.stok);
            printf("Price: ");
            scanf("%lf", &komponen.harga);
            komponen.nama[strcspn(komponen.nama, "\n")] = '\0';

            fseek(fdat, komponen_indeks[i].offset, SEEK_SET);
            fwrite(&komponen, sizeof(Barang), 1, fdat);
            fclose(fdat);
            printf("Data updated\n");
            return;
        }
    }
    fclose(fdat);
    printf("Data not found\n");
}

void view_indeks()
{
    load_index();
    FILE *fdat = fopen(data_file, "rb");
    if (!fdat)
    {
        file_error(data_file);
        return;
    }
    if (komponen_jumlah == 0)
    {
        printf("No data available\n");
        return;
    }

    qsort(komponen_indeks, komponen_jumlah, sizeof(Indeks), banding);
    double total_asset = 0.0;
    Barang component;
    printf("\nKode\t\tName\t\tStock\tPrice\n");
    for (int i = 0; i < komponen_jumlah; i++)
    {
        fseek(fdat, komponen_indeks[i].offset, SEEK_SET);
        fread(&component, sizeof(Barang), 1, fdat);
        printf("%s\t%s\t%d\t%.2f\n", component.kode, component.nama, component.stok, component.harga);
        total_asset += component.stok * component.harga;
    }
    fclose(fdat);
    printf("Assets value: %.2f\n", total_asset);
}

void noindeks()
{
    FILE *fdat = fopen(data_file, "rb");
    if (!fdat)
    {
        file_error(data_file);
        return;
    }
    double total_asset = 0;
    Barang component;

    printf("\nName\t\tStock\tPrice\n");
    while (fread(&component, sizeof(Barang), 1, fdat))
    {
        printf("%s\t%d\t%.2f\n", component.nama, component.stok, component.harga);
        total_asset += component.stok * component.harga;
    }
    fclose(fdat);
    printf("Assets value: %.2f\n", total_asset);
}

void hapus()
{
    char cari[kode_length];
    printf("Enter code to delete: ");
    scanf("%s", cari);
    load_index();
    FILE *fdat = fopen(data_file, "rb");
    FILE *ftemp = fopen("../data/temp.dat", "wb");
    FILE *fnew_index = fopen("../data/newindex.dat", "wb");
    if (!fdat)
    {
        if (!fdat)
            file_error(data_file);
        return;
    }
    Barang component;
    bool found = false;
    long offset = 0;
    for (int i = 0; i < komponen_jumlah; i++)
    {
        fseek(fdat, komponen_indeks[i].offset, SEEK_SET);
        fread(&component, sizeof(Barang), 1, fdat);

        if (strcmp(component.kode, cari) != 0)
        {
            fwrite(&component, sizeof(Barang), 1, ftemp);
            Indeks new_index;
            strcpy(new_index.kode, component.kode);
            new_index.offset = offset;
            fwrite(&new_index, sizeof(Indeks), 1, fnew_index);
            offset += sizeof(Barang);
        }
        else
        {
            found = true;
        }
    }
    fclose(fdat);
    fclose(ftemp);
    fclose(fnew_index);
    remove(data_file);
    rename("../data/temp.dat", data_file);
    remove(data_indeks);
    rename("../data/newindex.dat", data_indeks);
    if (found)
        printf("Data deleted\n");
    else
        printf("Data not found\n");
}

void keluar()
{
    printf("\nExiting program...\n");
    exit(0);
}

void menu()
{
    char input = '1', temp = '1', clear;
    printf("=== MENU ===\n");
    printf("1. Tambah data\n");
    printf("2. Ubah data\n");
    printf("3. Tampilkan data pakai index\n");
    printf("4. Tampilkan data tanpa index\n");
    printf("5. Hapus data\n");
    printf("6. Keluar\n");
    printf("Input:  ");
    while (1)
    {
        int ch = _getch();
        printf("\b");
        if (ch == 224)
        {
            int arah = _getch();
            if (temp >= '1' && temp <= '6')
            {
                if (arah == 72)
                    temp = (temp >= '6') ? '1' : ++temp; // arrow atas
                if (arah == 80)
                    temp = (temp <= '1') ? '6' : --temp; // arrow bawah
            }
            input = temp;
        }
        else if (ch == 13)
        { // enter
            switch (input)
            {
            case '1':
            case 'M':
                tambah();
                break;
            case '2':
            case 'U':
                ubah();
                break;
            case '3':
            case 'X':
                view_indeks();
                break;
            case '4':
            case 'T':
                noindeks();
                break;
            case '5':
            case 'H':
                hapus();
                break;
            case '6':
            case 'K':
                keluar();
                return;
            default:
                printf("\nInput invalid");
                break;
            }
            printf("\nClear screen [y/n]: ");
            scanf(" %c", &clear);
            if (toupper(clear) == 'Y')
            {
                clearscreen();
                printf("=== MENU ===\n");
                printf("1. Tambah data\n");
                printf("2. Ubah data\n");
                printf("3. Tampilkan data pakai index\n");
                printf("4. Tampilkan data tanpa index\n");
                printf("5. Hapus data\n");
                printf("6. Keluar\n");
            }
            printf("\nInput: ");
        }
        else
        {
            input = toupper(ch);
            if (input >= '1' && input <= '6')
            {
                temp = input;
            }
            else
            {
                switch (input)
                {
                case 'M':
                    temp = '1';
                    break;
                case 'U':
                    temp = '2';
                    break;
                case 'X':
                    temp = '3';
                    break;
                case 'T':
                    temp = '4';
                    break;
                case 'H':
                    temp = '5';
                    break;
                case 'K':
                    temp = '6';
                    break;
                default:
                    break;
                }
            }
        }
        printf("%c", input);
    }
}