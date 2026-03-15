#include <stdio.h>
#include <string.h>
#include <math.h>
// acc
int main()
{
    int input;
    char string[101];
    scanf("%d", &input);
    scanf("%s", string);
    int temp = 1, k = 0;
    char hasil[101];
    int len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (string[i] == '_')
        {
            string[i] = ' ';
        }

        hasil[k] = string[i];

        k += input;
        if (k >= len)
        {
            k = temp;
            temp++;
        }
    }
    for (int i = 0; i < len; i++)
    {
        printf("%c", hasil[i]);
    }
    return 0;
}