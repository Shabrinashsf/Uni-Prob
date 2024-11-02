#include <stdio.h>
#include <string.h>
// flipagram
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char cmd[8];
        scanf("%s", cmd);
        char strA[1000];
        char strB[1000];
        char temp[1000];
        scanf("%s", strA);
        scanf("%s", strB);
        int length = strlen(strA);
        int a[26];
        int b[26];

        for (int i = 0; i < 26; i++)
        {
            a[i] = 0;
            b[i] = 0;
        }

        if (strcmp(cmd, "FLIP") == 0)
        {
            for (int i = 0; i < length; i++)
            {
                temp[i] = strB[length - 1 - i];
            }
            temp[length] = '\0';

            if (strcmp(temp, strA) == 0)
            {
                printf("Flip %s to get %s", strA, strB);
            }
            else
            {
                printf("This cannot lah bro");
            }
        }

        else if (strcmp(cmd, "ANAGRAM") == 0)
        {

            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if ((strA[i] - 97) == j)
                    {
                        a[j] += 1;
                    }
                    if ((strB[i] - 97) == j)
                    {
                        b[j] += 1;
                    }
                }
            }

            int sama = 0;
            for (int i = 0; i < 26; i++)
            {
                if (a[i] != b[i])
                {
                    sama = 1;
                    break;
                }
            }

            if (sama == 0)
            {
                printf("Hhm %s can be arranged into %s", strA, strB);
            }
            else
            {
                printf("This cannot lah bro");
            }
        }

        printf("\n");
    }
}