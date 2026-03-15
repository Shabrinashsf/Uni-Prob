#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_FILE "../data/component.dat"
#define INDEX_FILE "../data/index.dat"
#define TOTAL_DATA 70

typedef struct
{
    char kode[7];
    char nama[26]; // null terminator
    int stok;
    double harga;
} Komponen;

typedef struct
{
    char kode[7];
    long offset;
} Index;

const char *komponen_motor[] = {
    "busi", "karburator", "aki", "kampas rem", "rantai", "velg", "lampu depan", "lampu belakang", "shockbreaker",
    "speedometer", "jok", "starter elektrik", "kick starter", "radiator", "spion", "ban depan", "ban belakang",
    "kopling", "karburator cadangan", "filter udara"};

const char *komponen_mobil[] = {
    "aki", "alternator", "kampas rem", "lampu kabut", "wiper", "radiator", "dashboard", "shockbreaker", "velg",
    "knalpot", "ECU", "sensor O2", "rem cakram", "filter oli", "AC compressor", "power steering", "ban serep",
    "speedometer", "lampu rem", "klakson"};

const char *komponen_pesawat[] = {
    "turbin", "sayap", "ekor", "mesin jet", "rudder", "spoiler", "sistem navigasi", "kabin", "jendela", "rem udara",
    "radar", "lampu landing", "sistem hidrolik", "ban utama", "kopkit", "avionik", "autopilot", "sensor tekanan",
    "kompas", "parasut darurat"};

const char *komponen_kapal[] = {
    "baling-baling", "jangkar", "haluan", "buritan", "kemudi", "dashboard", "sonar", "bodi kapal",
    "mesin kapal", "pelampung"};

void isi_nama_dengan_padding(char *dest, const char *sumber)
{
    int len = strlen(sumber);
    strncpy(dest, sumber, 25);
    for (int i = len; i < 25; i++)
        dest[i] = ' ';
    dest[25] = '\0'; //+null
}

void tulis_data()
{
    FILE *fdata = fopen(DATA_FILE, "wb");
    FILE *findex = fopen(INDEX_FILE, "wb");
    if (!fdata || !findex)
    {
        perror("Gagal membuka file");
        exit(1);
    }

    Komponen all[TOTAL_DATA];
    int idx = 0, i;

    // Motor
    for (i = 0; i < 20; i++)
    {
        sprintf(all[idx].kode, "d02%03d", i + 1);
        isi_nama_dengan_padding(all[idx].nama, komponen_motor[i]);
        all[idx].stok = rand() % 100 + 1;
        all[idx].harga = (rand() % 100000 + 1000) / 10.0;
        idx++;
    }

    // Mobil
    for (i = 0; i < 20; i++)
    {
        sprintf(all[idx].kode, "d04%03d", i + 1);
        isi_nama_dengan_padding(all[idx].nama, komponen_mobil[i]);
        all[idx].stok = rand() % 100 + 1;
        all[idx].harga = (rand() % 200000 + 5000) / 10.0;
        idx++;
    }

    // Pesawat
    for (i = 0; i < 20; i++)
    {
        sprintf(all[idx].kode, "u00%03d", i + 1);
        isi_nama_dengan_padding(all[idx].nama, komponen_pesawat[i]);
        all[idx].stok = rand() % 50 + 1;
        all[idx].harga = (rand() % 1000000 + 100000) / 10.0;
        idx++;
    }

    // Kapal
    for (i = 0; i < 10; i++)
    {
        sprintf(all[idx].kode, "l00%03d", i + 1);
        isi_nama_dengan_padding(all[idx].nama, komponen_kapal[i]);
        all[idx].stok = rand() % 70 + 1;
        all[idx].harga = (rand() % 300000 + 5000) / 10.0;
        idx++;
    }

    for (i = TOTAL_DATA - 1; i > 0; i--)
    { // random
        int j = rand() % (i + 1);
        Komponen temp = all[i];
        all[i] = all[j];
        all[j] = temp;
    }

    for (i = 0; i < TOTAL_DATA; i++)
    {
        long offset = ftell(fdata);
        fwrite(&all[i], sizeof(Komponen), 1, fdata);

        Index idx_entry;
        strcpy(idx_entry.kode, all[i].kode);
        idx_entry.offset = offset;
        fwrite(&idx_entry, sizeof(Index), 1, findex);
    }

    fclose(fdata);
    fclose(findex);

    printf("Berhasil membuat %d data di '%s' dan index di '%s'\n", TOTAL_DATA, DATA_FILE, INDEX_FILE);
}

int main()
{
    srand(time(NULL));
    tulis_data();
    return 0;
}