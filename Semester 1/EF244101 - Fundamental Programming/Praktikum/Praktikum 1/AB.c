// Write by Shabrina Amalia Safaana

#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d %d", &a, &b);
    scanf("%d", &c);

    if (a >= 1 && a <= 100000)
    {
        if (b >= 1 && b <= 100000)
        {
            if (c >= 1 && c <= 5)
            {
                if (c == 1)
                {
                    printf("%d", a << b);
                }
                else if (c == 2)
                {
                    printf("%d", a >> b);
                }
                else if (c == 3)
                {
                    printf("%d", a & b);
                }
                else if (c == 4)
                {
                    printf("%d", a | b);
                }
                else
                {
                    printf("%d", a ^ b);
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
