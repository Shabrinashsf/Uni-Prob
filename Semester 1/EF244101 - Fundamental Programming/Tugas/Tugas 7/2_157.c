#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
    int finish = 1;
    while (finish == 1)
    {
        char color_codes[10][7] = {
            "black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "gray", "white"};
        char input[3][7];
        printf("Band 1 => ");
        scanf("%s", &input[0]);
        printf("Band 2 => ");
        scanf("%s", &input[1]);
        printf("Band 3 => ");
        scanf("%s", &input[2]);

        int digitOne, digitTwo, multiplier;
        for (int i = 0; i < 10; i++)
        {
            if (!strcmp(input[0], color_codes[i]))
            {
                digitOne = i;
            }
            if (!strcmp(input[1], color_codes[i]))
            {
                digitTwo = i;
            }
            if (!strcmp(input[2], color_codes[i]))
            {
                multiplier = i;
            }
        }

        // kita jadiin kilo ohm aja, kilo itu kalo n == 2
        int digitValue = (digitOne * 10 + digitTwo);
        int value = digitValue * pow(10, multiplier);
        double finalValue = (double)(value) / 1000;

        printf("Resistance value: %.3lf kilo-ohms\n", finalValue);
        printf("Do you want to decode another resistor?\n");
        char lanjut;
        printf("=> ");
        getchar();
        scanf("%c", &lanjut);
        if (lanjut != 'y')
        {
            finish = 0;
        }
    }
}