void runFillDaysInMonths();
short getYearFromFile();
void writeYearInFile();
void fillDaysInMonths();
char* getDaysInEveryMonthFromFile();
void writeQuantityDaysInEveryMonthInFile();
short* getArrayQuantityDaysInEveryMonthOfYear();
short computeQuantityDaysInMonthOfYear(short month, short year);
SYSTEMTIME getDate();


#define FILE_NAME_CONTAINS_DAYS_IN_MONTHS "daysInEveryMonth.txt"
#define FILE_NAME_CONTAINS_YEAR "year.txt"


short DaysInMonths[12];
short CounterMonths = 0;


void runFillDaysInMonths()
{
    short yearInFile = getYearFromFile();
    SYSTEMTIME date = getDate();
    FILE* file;

    if (yearInFile == date.wYear)
    {
        if ((file = fopen(FILE_NAME_CONTAINS_DAYS_IN_MONTHS, "r")) == NULL)
        {
            writeQuantityDaysInEveryMonthInFile();
            fillDaysInMonths();
        }
        else
        {
            fillDaysInMonths();
        }
    }
    else
    {
        writeYearInFile();
        writeQuantityDaysInEveryMonthInFile();
        fillDaysInMonths();
    }
}

short getYearFromFile()
{
    FILE *file;
    SYSTEMTIME date = getDate();
    static short year;

    if ((file = fopen(FILE_NAME_CONTAINS_YEAR, "r")) == NULL)
    {
        printf("Can't open 'year.txt'");
    }
    else
    {
        fscanf(file, "%d", &year);
        fclose(file);
        
        return year;
    }
}

void writeYearInFile()
{
    FILE* file;
    SYSTEMTIME date = getDate();

    if ((file = fopen(FILE_NAME_CONTAINS_YEAR, "w")) == NULL)
    {
        printf("Can't create 'year.txt'");
    }
    else
    {
        fprintf(file, "%d", date.wYear);
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
                DaysInMonths[CounterMonths] = 30;
                ++CounterMonths;
            }
            else if (stringDaysInMonths[j] == '1')
            {
                DaysInMonths[CounterMonths] = 31;
                ++CounterMonths;
            }
        }
        else if (stringDaysInMonths[j] == '2')
        {
            ++j;
            if (stringDaysInMonths[j] == '9')
            {
                DaysInMonths[CounterMonths] = 29;
                ++CounterMonths;
            }
            else if (stringDaysInMonths[j] == '8')
            {
                DaysInMonths[CounterMonths] = 28;
                ++CounterMonths;
            }
        }
    }
}

char* getDaysInEveryMonthFromFile()
{
    FILE* file;
    static char string[24];
    
    if ((file = fopen(FILE_NAME_CONTAINS_DAYS_IN_MONTHS, "r")) == NULL)
    {
        printf("Can't read 'daysInEveryMonth.txt'");
    }
    else
    {
        fscanf(file, "%s", string);
        fclose(file);

        return string;
    }
}

void writeQuantityDaysInEveryMonthInFile()
{
    FILE* file;
    short* ptrToDaysInEveryMonth = getArrayQuantityDaysInEveryMonthOfYear();

    if ((file = fopen(FILE_NAME_CONTAINS_DAYS_IN_MONTHS, "w")) == NULL)
    {
        printf("Can't create 'daysInEveryMonth.txt'");
    }
    else
    {
        for (int j = 0; j < 12; ++j)
        {
            fprintf(file, "%d", ptrToDaysInEveryMonth[j]);
        }

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