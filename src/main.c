/* @Author: Daniil Maslov */

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

SYSTEMTIME getDate();
short* getArrayQuantityDaysInEveryMonthOfYear();
short computeQuantityDaysInMonthOfYear(short month, short year);

void main()
{
    
}

SYSTEMTIME getDate()
{
    SYSTEMTIME date;
    GetLocalTime(&date);

    return date;
}

short* getArrayQuantityDaysInEveryMonthOfYear()
{
    SYSTEMTIME date = getDate();
    static short quantityDaysInMonths[12];

    for (int i = 0; i < 12; ++i)
    {
        quantityDaysInMonths[i] = computeQuantityDaysInMonthOfYear(i+1, date.wYear);
    }

    return quantityDaysInMonths;
}

short computeQuantityDaysInMonthOfYear(short month, short year)
{
    double quantity = 28 + ((int)(month + floor(month / 8)) % 2) + 2 % month +
        floor((1 + (1 - (year % 4 + 2) % (year % 4 + 1)) * ((year % 100 + 2) % (year % 100 + 1)) +
            (1 - (year % 400 + 2) % (year % 400 + 1))) / month) + floor(1 / month) -
                floor(((1 - (year % 4 + 2) % (year % 4 + 1)) * ((year % 100 + 2) % (year % 100 + 1)) +
                    (1 - (year % 400 + 2) % (year % 400 + 1))) / month);
    
    return quantity;
}