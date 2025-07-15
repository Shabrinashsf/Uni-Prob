#include <stdio.h>

typedef struct
{
    long long hp;
    long long attack;
    long long defense;
    long long speed;
    char trainer[20];
    char pokemon[20];
    long long avg;
} pokemon;

// pemenang = pokemon dengan rata rata atribut tertinggi
// tinggal dibuat rata rata aja

void solve(pokemon *data, int banyakData)
{
    for (int i = 0; i < banyakData; i++)
    {
        data[i].avg = (data[i].hp + data[i].attack + data[i].defense + data[i].speed) / 4;
    }

    long long max = 0;
    int index = 0;
    for (int i = 0; i < banyakData; i++)
    {
        if (data[i].avg > max)
        {
            max = data[i].avg;
            index = i;
        }
    }
    printf("%s wins! %s said ez", data[index].pokemon, data[index].trainer);
}

int main()
{
    int n;
    scanf("%d", &n);
    pokemon data[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %lld %lld %lld %lld", data[i].trainer, data[i].pokemon, &data[i].hp, &data[i].attack, &data[i].defense, &data[i].speed);
    }

    solve(data, n);
}