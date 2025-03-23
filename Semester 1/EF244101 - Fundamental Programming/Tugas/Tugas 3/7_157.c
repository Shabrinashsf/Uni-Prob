#include <stdio.h>

int kabisat(int year)
{
    if (year % 100 == 0)
    {
        if (year % 400 == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (year % 4 == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int main()
{
    int day, month, year, leap, total;
    printf("Enter date month day, year:\n");
    scanf("%d %d %d", &month, &day, &year);
    leap = kabisat(year);

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day > 31)
        {
            return 0;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    if (leap == 1)
    {
        if (month == 2)
        {
            if (day > 29)
            {
                return 0;
            }
        }
        if (month == 1)
        {
            total = day;
        }
        else if (month == 2)
        {
            total = 31 + day;
        }
        else if (month == 3)
        {
            total = 60 + day;
        }
        else if (month == 4)
        {
            total = 91 + day;
        }
        else if (month == 5)
        {
            total = 121 + day;
        }
        else if (month == 6)
        {
            total = 152 + day;
        }
        else if (month == 7)
        {
            total = 182 + day;
        }
        else if (month == 8)
        {
            total = 213 + day;
        }
        else if (month == 9)
        {
            total = 244 + day;
        }
        else if (month == 10)
        {
            total = 274 + day;
        }
        else if (month == 11)
        {
            total = 305 + day;
        }
        else if (month == 12)
        {
            total = 335 + day;
        }
    }
    else
    {
        if (month == 2)
        {
            if (day > 28)
            {
                return 0;
            }
        }
        if (month == 1)
        {
            total = day;
        }
        else if (month == 2)
        {
            total = 31 + day;
        }
        else if (month == 3)
        {
            total = 59 + day;
        }
        else if (month == 4)
        {
            total = 90 + day;
        }
        else if (month == 5)
        {
            total = 120 + day;
        }
        else if (month == 6)
        {
            total = 151 + day;
        }
        else if (month == 7)
        {
            total = 181 + day;
        }
        else if (month == 8)
        {
            total = 212 + day;
        }
        else if (month == 9)
        {
            total = 243 + day;
        }
        else if (month == 10)
        {
            total = 273 + day;
        }
        else if (month == 11)
        {
            total = 304 + day;
        }
        else if (month == 12)
        {
            total = 334 + day;
        }
    }

    printf("%d %d, %d is day %d", month, day, year, total);
}