#include <stdio.h>

void tambah(int a, int b, int *c)
{
    *c = a + b;
}

int main()
{
    int satu;
    int dua;
    int tiga;
    scanf("%d %d", &satu, &dua);
    tambah(satu, dua, &tiga);
    printf("%d", tiga);
}