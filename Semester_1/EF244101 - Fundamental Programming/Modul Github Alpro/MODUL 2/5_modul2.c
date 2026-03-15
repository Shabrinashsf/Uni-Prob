#include <stdio.h>
#include <string.h>

int main()
{
    char s[100];
    int a = 0;
    int i = 0;
    int u = 0;
    int e = 0;
    int o = 0;
    gets(s);
    for (int k = 0; k <= strlen(s) - 1; k++)
    {
        if (s[k] == 'a' || s[k] == 'A')
        {
            a += 1;
        }
        else if (s[k] == 'i' || s[k] == 'I')
        {
            i += 1;
        }
        else if (s[k] == 'u' || s[k] == 'U')
        {
            u += 1;
        }
        else if (s[k] == 'e' || s[k] == 'E')
        {
            e += 1;
        }
        else if (s[k] == 'o' || s[k] == 'O')
        {
            o += 1;
        }
    }
    printf("A/a : %d\n", a);
    printf("I/i : %d\n", i);
    printf("U/u : %d\n", u);
    printf("E/e : %d\n", e);
    printf("O/o : %d\n", o);
}