void runFillDaysInMonths();
void fillDaysInMonths();
char* getDaysInEveryMonthFromFile();
void writeInFileArrayQuantityDaysInEveryMonthOfYear();
short* getArrayQuantityDaysInEveryMonthOfYear();
short computeQuantityDaysInMonthOfYear(short month, short year);
SYSTEMTIME getDate();


#define FILE_NAME "daysInEveryMonth.txt"


short daysInMonths[12];
short counterMonths = 0;

// TODO: надо делать runFillDaysInMonths, если текущий год соответствует году из файла
// т.е. нужно создать ещё одну функцию, которая записывает текущий год в файл.
// Если годы не совпадают -> запускаем writeInFile по новой.
void runFillDaysInMonths()
{
    FILE* file;
    if ((file = fopen(FILE_NAME, "r")) == NULL)
    {
        writeInFileArrayQuantityDaysInEveryMonthOfYear();
        fillDaysInMonths();
    }
    else
    {
        fillDaysInMonths();
    }
    
}

void fillDaysInMonths()
{
    char* stringDaysInMonths = getDaysInEveryMonthFromFile();

    for (int j = 0; j < 24; ++j)
    {
        if (stringDaysInMonths[j] == '3')
        {
            ++j;
            if (stringDaysInMonths[j] == '0')
            {
                daysInMonths[counterMonths] = 30;
                ++counterMonths;
            }
            else if (stringDaysInMonths[j] == '1')
            {
                daysInMonths[counterMonths] = 31;
                ++counterMonths;
            }
        }
        else if (stringDaysInMonths[j] == '2')
        {
            ++j;
            if (stringDaysInMonths[j] == '9')
            {
                daysInMonths[counterMonths] = 29;
                ++counterMonths;
            }
            else if (stringDaysInMonths[j] == '8')
            {
                daysInMonths[counterMonths] = 28;
                ++counterMonths;
            }
        }
    }
}

char* getDaysInEveryMonthFromFile()
{
    FILE* file;
    static char string[24];
    
    if ((file = fopen(FILE_NAME, "r")) == NULL)
    {
        printf("Не удалось прочесть файл daysInEveryMonth");
    }
    else
    {
        fscanf(file, "%s", string);
        fclose(file);

        return string;
    }
}

void writeInFileArrayQuantityDaysInEveryMonthOfYear()
{
    FILE* file;
    short* ptrToDaysInEveryMonth = getArrayQuantityDaysInEveryMonthOfYear();

    if ((file = fopen(FILE_NAME, "w")) == NULL)
    {
        printf("Не удалось создать файл daysInEveryMonth");
    }
    else
    {
        for (int j = 0; j < 12; ++j)
            fprintf(file, "%d", ptrToDaysInEveryMonth[j]);

        fclose(file);
    }
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

SYSTEMTIME getDate()
{
    SYSTEMTIME date;
    GetLocalTime(&date);

    return date;
}