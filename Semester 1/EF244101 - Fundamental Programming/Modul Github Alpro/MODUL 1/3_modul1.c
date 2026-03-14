#include <stdio.h>
// input I1 I2 I3 I4 => bilangan biner
// output A B C D E F G
// 0 0 0 0 == 1 1 1 1 1 1 0 
// 0 0 0 1 == 0 1 1 0 0 0 0 
// 0 0 1 0 == 1 1 0 1 1 0 1 
// 0 0 1 1 == 1 1 1 1 0 0 1 
// 0 1 0 0 == 0 1 1 0 0 1 1 
// 0 1 0 1 == 1 0 1 1 0 1 1 
// 0 1 1 0 == 1 0 1 1 1 1 1 
// 0 1 1 1 == 1 1 1 0 0 0 0 
// 1 0 0 0 == 1 1 1 1 1 1 1 
// 1 0 0 1 == 1 1 1 1 0 1 1 

int main()
{
    int I1, I2, I3, I4, number;
    scanf("%d %d %d %d", &I1, &I2, &I3, &I4);

    number = (I1 * 8) + (I2 * 4) + (I3 * 2) + (I4 * 1);

    if (number <= 9)
    {
        switch (number)
        {
        case 0:
            printf("%s", "1 1 1 1 1 1 0");
            break;
        case 1:
            printf("%s", "0 1 1 0 0 0 0");
            break;
        case 2:
            printf("%s", "1 1 0 1 1 0 1");
            break;
        case 3:
            printf("%s", "1 1 1 1 0 0 1");
            break;
        case 4:
            printf("%s", "0 1 1 0 0 1 1");
            break;
        case 5:
            printf("%s", "1 0 1 1 0 1 1");
            break;
        case 6:
            printf("%s", "1 0 1 1 1 1 1");
            break;
        case 7:
            printf("%s", "1 1 1 0 0 0 0");
            break;
        case 8:
            printf("%s", "1 1 1 1 1 1 1");
            break;
        case 9:
            printf("%s", "1 1 1 1 0 1 1");
            break;
        }
    }
    else
    {
        printf("%s", "0 0 0 0 0 0 0");
    }
    return 0;
}