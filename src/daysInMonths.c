/* @Author: Daniil Maslov */

SYSTEMTIME getDate();
short getQuantityDaysInMonth(short month);
short computeQuantityDaysInMonthOfYear(short month, short year);


SYSTEMTIME getDate()
{
    SYSTEMTIME date;
    GetLocalTime(&date);

    return date;
}

short getQuantityDaysInMonth(short month) // колво дней в определенном месяце
{
    SYSTEMTIME date = getDate();
    computeQuantityDaysInMonthOfYear(month, date.wYear);
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