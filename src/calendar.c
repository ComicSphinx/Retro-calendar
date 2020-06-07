/* @Author: Daniil Maslov*/

typedef struct
{
    short monthDays[31];
    short numberCursor;
    COORD numbersCoords[31];
    COORD coordsCursor;

} CalendarDays;

typedef struct
{
    short left;
    short right;
    short top;
    short bottom;
} ConsoleSize;


CalendarDays calendarDays;
HANDLE HStdOut;
CONSOLE_SCREEN_BUFFER_INFO CsbInfo;

void moveCursor();
void installCursors();
void redrawNumber();
char getMovement();
void drawCalendar();
void fillCalendarDays(short daysNumber);
COORD getStartPosition();
ConsoleSize getConsoleSize();
void drawMonthByDays(COORD startPosition);

void moveCursor()
{
    char c;
    
    installCursors();

    while (1)
    {
        c = getMovement();

        if (c == 'w')
        {
            printf("w pressed");
            calendarDays.numberCursor -= 7;
            redrawNumber();
        }
        else if (c == 'a')
        {
            printf("a pressed");
            calendarDays.numberCursor--;
            redrawNumber();
        }
        else if (c == 's')
        {
            printf("s pressed");
            calendarDays.numberCursor += 7;
            redrawNumber();
        }
        else if (c == 'd')
        {
            printf("d pressed");
            calendarDays.numberCursor++;
            redrawNumber();
        }
    }
}

void installCursors()
{
    SYSTEMTIME date = getDate();

    for (int j = 30; j > 28; --j)
    {
        if (calendarDays.monthDays[j] != 0)
        {
            calendarDays.numberCursor = calendarDays.monthDays[date.wDay - 1];
            calendarDays.coordsCursor = calendarDays.numbersCoords[date.wDay - 1];
            SetConsoleCursorPosition(HStdOut, calendarDays.coordsCursor);

            break;
        }
    }
}

void redrawNumber()
{
    calendarDays.coordsCursor = calendarDays.numbersCoords[calendarDays.numberCursor - 1];
    SetConsoleCursorPosition(HStdOut, calendarDays.coordsCursor);
    printf("%d", calendarDays.numberCursor);
}

char getMovement()
{
    char c;
    
    if ((c = getchar()) != '.')
    {
        return c;
    }
}

void drawCalendar()
{
    HStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(HStdOut, &CsbInfo);
    SYSTEMTIME date = getDate();
    short numberOfDays = getDaysInCurrentMonthFromFile(date.wMonth);

    fillCalendarDays(numberOfDays);

    COORD startPosition = getStartPosition();
    drawMonthByDays(startPosition);
}

void fillCalendarDays(short daysNumber)
{
    for (int j = 0; j < daysNumber; ++j)
    {
        calendarDays.monthDays[j] = j+1;
    }
}

COORD getStartPosition()
{
    COORD startPosition;
    ConsoleSize consoleSize = getConsoleSize();

    startPosition.X = ((consoleSize.right / 2) / 2);
    short x = (startPosition.X / 2) / 2;
    startPosition.X += x*3;

    startPosition.Y = 2;

    return startPosition;
}

ConsoleSize getConsoleSize()
{
    ConsoleSize consoleSize;
    consoleSize.left = CsbInfo.srWindow.Left;
    consoleSize.right = CsbInfo.srWindow.Right;
    consoleSize.top = CsbInfo.srWindow.Top;
    consoleSize.bottom = CsbInfo.srWindow.Bottom;

    return consoleSize;
}

void drawMonthByDays(COORD cursorPos)
{
    long unsigned int cWrittenChars;
    short startCursorPosX = cursorPos.X;
    calendarDays.monthDays[0] = 1;
    short i = 0;

    system("cls");

    for (short rows = 0; rows < 5; ++rows)
    {
        for (short columns = 0; columns < 7; ++columns)
        {
            SetConsoleCursorPosition(HStdOut, cursorPos);
            
            if (calendarDays.monthDays[i] != 0)
            {
                calendarDays.numbersCoords[i].X = cursorPos.X;
                calendarDays.numbersCoords[i].Y = cursorPos.Y;
                printf("%d", calendarDays.monthDays[i]);
                ++i;
            }
            
            cursorPos.X += 3;
        }
        cursorPos.X = startCursorPosX;
        cursorPos.Y += 3;
    }
}
