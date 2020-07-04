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
char WeekDays[7][3] = {"Mon", "Tue", 
                       "Wed", "Thu", 
                       "Fri", "Sat", 
                       "Sun"};

char Months[12][3] = {"Jan", "Feb", "Mar", 
                      "Apr", "May", "Jun", 
                      "Jul", "Aug", "Sep", 
                      "Oct", "Nov", "Dec"};

void drawCalendar();
void fillCalendarDays(short daysNumber);
COORD getStartPosition();
ConsoleSize getConsoleSize();
void drawMonthByDays(COORD cursorPos);
void drawNowDate();
COORD getCoordsToDrawDate();
void drawTitleMonth(WORD month);
COORD getCoordsToDrawTitleMonth();
void moveCursor();
void installCursors();
void redrawNumber();


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

    startPosition.Y = 6;

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

void drawNowDate()
{
    SYSTEMTIME date = getDate();
    COORD cursor = getCoordsToDrawDate();

    SetConsoleCursorPosition(HStdOut, cursor);
    
    printf("Now:   ");
    printf("%c%c%c | ", Months[date.wMonth-1][0], Months[date.wMonth-1][1], Months[date.wMonth-1][2]);
    printf("%d | ", date.wDay);
    printf("%c%c%c", WeekDays[date.wDayOfWeek-1][0], WeekDays[date.wDayOfWeek-1][1], WeekDays[date.wDayOfWeek-1][2]);
}

COORD getCoordsToDrawDate()
{
    COORD coords = getStartPosition();
    coords.Y += 17;

    return coords;
}

void drawTitleMonth(WORD month)
{
    COORD cursor = getCoordsToDrawTitleMonth();
    SetConsoleCursorPosition(HStdOut, cursor);

    printf("< %c%c%c >", Months[month-1][0], Months[month-1][1], Months[month-1][2]);
}

COORD getCoordsToDrawTitleMonth()
{
    COORD coords = getStartPosition();
    coords.Y -= 3;
    // 21 is width of calendar
    coords.X += (21 / 3);

    return coords;
}

void moveCursor()
{
    char c;
    
    installCursors();

    while (1)
    {
        c = getchar();

        if (c == 'w')
        {
            calendarDays.numberCursor -= 7;
        }
        else if (c == 'a')
        {
            calendarDays.numberCursor--;
        }
        else if (c == 's')
        {
            calendarDays.numberCursor += 7;
        }
        else if (c == 'd')
        {
            calendarDays.numberCursor++;
        }
        else if (c == '.')
        {
            exit(1);
        }
        
        redrawNumber();
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
