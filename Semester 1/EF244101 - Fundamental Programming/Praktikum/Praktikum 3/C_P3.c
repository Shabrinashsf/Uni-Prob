// Write by Shabrina Amalia Safaana
// password

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isStrong = true;

// MULAI NGODING DARI SINI
int CheckNumber(char pass[])
{
    int len = strlen(pass);
    int numAda = 0;
    for (int i = 0; i < len; i++)
    {
        if (pass[i] == '0' || pass[i] == '1' || pass[i] == '2' || pass[i] == '3' || pass[i] == '4' || pass[i] == '5' || pass[i] == '6' || pass[i] == '7' || pass[i] == '8' || pass[i] == '9')
        {
            numAda += 1;
        }
    }
    if (numAda == 0)
    {
        isStrong = false;
        return 0;
    }
}

int CheckUppercase(char pass[])
{
    int len = strlen(pass);
    int kapitalAda = 0;
    for (int i = 0; i < len; i++)
    {
        if (pass[i] >= 'A' && pass[i] <= 'Z')
        {
            kapitalAda += 1;
        }
    }
    if (kapitalAda == 0)
    {
        isStrong = false;
        return 0;
    }
}

int CheckKey(char pass[], int key)
{
    int temp = 0;
    int len = strlen(pass);
    for (int i = 0; i < len; i++)
    {
        if (pass[i] == '0')
        {
            temp += 0;
        }
        else if (pass[i] == '1')
        {
            temp += 1;
        }
        else if (pass[i] == '2')
        {
            temp += 2;
        }
        else if (pass[i] == '3')
        {
            temp += 3;
        }
        else if (pass[i] == '4')
        {
            temp += 4;
        }
        else if (pass[i] == '5')
        {
            temp += 5;
        }
        else if (pass[i] == '6')
        {
            temp += 6;
        }
        else if (pass[i] == '7')
        {
            temp += 7;
        }
        else if (pass[i] == '8')
        {
            temp += 8;
        }
        else if (pass[i] == '9')
        {
            temp += 9;
        }
    }
    if (temp == key)
    {
        return temp;
    }
    else
    {
        isStrong = false;
        return 0;
    }
}

// NGODING SAMPE SINI, mengedit kode di bawah adalah tindakan ilegal

int main()
{
    char password[128];
    int key;
    scanf("%s %d", password, &key);
    if (!CheckNumber(password))
        printf("Password needs number\n");
    if (!CheckUppercase(password))
        printf("Password requires at least one uppercase letter\n");
    if (!CheckKey(password, key))
        printf("Digits in password not equal to key\n");
    if (isStrong)
        printf("Password is strong, just like you\n");
    else
        printf("Weak password, fix your mistakes\n");
}
