/* @Author: Daniil Maslov */

short getQuantityDaysInMonth(short month);
short* getQuantityDaysInMonths();
SYSTEMTIME getDate();
short computeQuantityDaysInMonthOfYear(short month, short year);

short getQuantityDaysInMonth(short month)
{
    short* days = getQuantityDaysInMonths();
    return days[month-1];
}

short* getQuantityDaysInMonths()
{
    SYSTEMTIME date = getDate();
    short* quantityDaysInMonths = malloc(12*sizeof(short));

    for (int i = 0; i < 12; ++i)
    {
        quantityDaysInMonths[i] = computeQuantityDaysInMonthOfYear(i+1, date.wYear);
    }

    return quantityDaysInMonths;
}

SYSTEMTIME getDate()
{
    SYSTEMTIME date;
    GetLocalTime(&date);

    return date;
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