#include <stdio.h>
#include <string.h>
int main()
{
    int a;
    char s[1000];
    scanf("%d", &a);
    getchar();
    gets(s);
    int p = strlen(s);
    char temp[p];

    if (a > 0)
    {
        for (int i = 0; i < p; i++)
        {
            if (s[i] == ' ')
            {
                temp[i] = ' ';
            }
            else if (s[i] != '\0')
            {
                if (s[i] + a >= 122)
                {
                    temp[i] = s[i] - 26 + a + 2;
                }
                else if (s[i] + a < 122)
                {
                    temp[i] = s[i] + a;
                }
            }
            temp[p] = '\0';
        }
    }
    else
    {
        for (int i = 0; i < p; i++)
        {
            int awal = s[i];
            if (s[i] == ' ')
            {
                temp[i] = ' ';
            }
            else if (s[i] != '\0')
            {
                if ((awal + 26 + a) > 122)
                {
                    temp[i] = s[i] + a;
                }
                else if ((awal + 26 + a) <= 122)
                {
                    temp[i] = awal + 26 + a;
                }
            }
            temp[p] = '\0';
        }
    }

    printf("%s", temp);
}