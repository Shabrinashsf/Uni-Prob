#include <stdio.h>
#include <string.h>

int main()
{
    char snake[100];
    gets(snake);
    for (int i = 0; i < strlen(snake); i++)
    {
        // untuk ngubah semua ke lowercase
        if (snake[i] == '_')
        {
            if (snake[i + 1] >= 65 && snake[i] <= 90)
            {
                continue;
            }
        }
    }
    // ngubah setelah _ menjadi kapital dan menghilangkan _
    for (int k = 0; k < strlen(snake); k++)
    {
        if (snake[k] == '_')
        {
            snake[k] = snake[k + 1];
        }
        snake[k + 1] = snake[k + 2];
    }
}