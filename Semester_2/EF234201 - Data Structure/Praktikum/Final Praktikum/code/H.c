#include <stdio.h>
#include <string.h>

int main()
{
    char s[100001];
    scanf("%s", s);

    int freq[26] = {0};
    int len = strlen(s);

    for (int i = 0; i < len; i++)
    {
        freq[s[i] - 'a']++;
    }

    for (int i = 0; i < len; i++)
    {
        if (freq[s[i] - 'a'] == 1)
        {
            printf("%d\n", i);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}

/*
Masukan
programmingcontest
Keluaran
0

Input
aabbccddeeff
Output
-1

Input
statistics
Output
2
*/