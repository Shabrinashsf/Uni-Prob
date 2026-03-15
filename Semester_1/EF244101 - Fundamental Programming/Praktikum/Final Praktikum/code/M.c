#include <stdio.h>
// acc
int best_cow(int q, int k)
{
    if (q == 1)
    {
        return 0;
    }
    return (best_cow(q - 1, k) + k) % q;
}

int main()
{
    int q, k;
    scanf("%d %d", &q, &k);
    int cow = best_cow(q, k) + 1;
    printf("yapp, sapi ke %d sepertinya memang yang terbaik.", cow);
}