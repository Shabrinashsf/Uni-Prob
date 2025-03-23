#include <stdio.h>

void checkWinner(int a[], int b[], int c[], int d[], int hasil[], int *sum, float percentage[], char *win, int *run, char *paslon1, char *paslon2, int *maxPaslon1, int *maxPaslon2)
{
    *sum = 0;
    *run = 0;
    *maxPaslon1 = 0;
    *maxPaslon2 = 0;
    *win = 0;

    int tempA = 0, tempB = 0, tempC = 0, tempD = 0;
    for (int i = 0; i < 5; i++)
    {
        tempA += a[i];
        tempB += b[i];
        tempC += c[i];
        tempD += d[i];
    }

    hasil[0] = tempA;
    hasil[1] = tempB;
    hasil[2] = tempC;
    hasil[3] = tempD;

    for (int i = 0; i < 4; i++)
    {
        *sum += hasil[i];
    }

    for (int i = 0; i < 4; i++)
    {
        percentage[i] = ((float)hasil[i] / (float)*sum) * 100.0;
    }

    int indexWinner = -1;
    for (int i = 0; i < 4; i++)
    {
        if (percentage[i] >= 50)
        {
            *win = 'A' + i; // Kandidat A adalah index 0, B adalah index 1, ds
            indexWinner = i;
        }
        else
        {
            (*run)++;
        }
    }

    if (*win == 0 && *run == 4)
    {
        // Mencari dua paslon dengan suara tertinggi
        for (int i = 0; i < 4; i++)
        {
            if (percentage[i] > *maxPaslon1)
            {
                *maxPaslon2 = *maxPaslon1; // Pindahkan nilai max1 ke max2
                *paslon2 = *paslon1;       // Pindahkan kandidat max1 ke paslon2

                *maxPaslon1 = percentage[i];
                *paslon1 = 'A' + i;
            }
            else if (percentage[i] > *maxPaslon2)
            {
                *maxPaslon2 = percentage[i];
                *paslon2 = 'A' + i;
            }
        }
        printf("A runoff between candidate %c and candidate %c\n", *paslon1, *paslon2);
    }
    else if (*win != 0)
    {
        printf("The winner is candidate %c with total percentage %.3f\n", *win, percentage[indexWinner]);
    }
}

int main()
{
    int aCandidate[5] = {192, 147, 186, 114, 267};
    int bCandidate[5] = {48, 90, 12, 21, 13};
    int cCandidate[5] = {206, 312, 121, 408, 382};
    int dCandidate[5] = {37, 21, 38, 39, 29};
    int cSementara[5] = {206, 312, 121, 108, 382};
    int hasil[4];
    int tempA = 0, tempB = 0, tempC = 0, tempD = 0;
    int total = 0;
    float persen[4];
    char winner;
    int runoff = 0;
    char candidate1, candidate2;
    int max1 = 0, max2 = 0;

    printf("%4c %8c %4c %s %4c %s %4c %s %4c %s\n", ' ', ' ', ' ', "Candidate", ' ', "Candidate", ' ', "Candidate", ' ', "Candidate");
    printf("%4c %s %8c %s %12c %s %12c %s %12c %s\n", ' ', "Precinct", ' ', "A", ' ', "B", ' ', "C", ' ', "D");
    printf("_____________________________________________________________________________\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%7c %d %11c %d %10c %d %10c %d %10c %d\n", ' ', i + 1, ' ', aCandidate[i], ' ', bCandidate[i], ' ', cCandidate[i], ' ', dCandidate[i]);
    }
    printf("_____________________________________________________________________________\n");

    checkWinner(aCandidate, bCandidate, cCandidate, dCandidate, hasil, &total, persen, &winner, &runoff, &candidate1, &candidate2, &max1, &max2);

    printf("\n");
    printf("Data when candidate C receiving only 108 votes in Precinct 4:\n");
    printf("\n");

    printf("%4c %8c %4c %s %4c %s %4c %s %4c %s\n", ' ', ' ', ' ', "Candidate", ' ', "Candidate", ' ', "Candidate", ' ', "Candidate");
    printf("%4c %s %8c %s %12c %s %12c %s %12c %s\n", ' ', "Precinct", ' ', "A", ' ', "B", ' ', "C", ' ', "D");
    printf("_____________________________________________________________________________\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%7c %d %11c %d %10c %d %10c %d %10c %d\n", ' ', i + 1, ' ', aCandidate[i], ' ', bCandidate[i], ' ', cSementara[i], ' ', dCandidate[i]);
    }
    printf("_____________________________________________________________________________\n");
    checkWinner(aCandidate, bCandidate, cSementara, dCandidate, hasil, &total, persen, &winner, &runoff, &candidate1, &candidate2, &max1, &max2);
}