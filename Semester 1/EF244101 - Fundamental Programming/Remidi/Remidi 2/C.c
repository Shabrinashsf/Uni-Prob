#include <stdio.h>
// untuk labirin
int main()
{
    int n;
    int p = 0;
    scanf("%d", &n);
    char labirin[3][3];
    int temp[n*n];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < n * n; k++){
                temp[k] = p += 1;
            }
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (j == n - 1 && i == 0){
                printf("%d ", p += 1);
            }
        }
    }
}