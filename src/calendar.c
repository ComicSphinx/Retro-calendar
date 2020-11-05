/* @Author: Daniil Maslov */

typedef struct
{
    short numberCursor;
    COORD numbersCoords[31];
    COORD coordsCursor;
} CursorCoords;

typedef struct
{
    short leftPoint;
    short rightPoint;
    short topPoint;
    short bottomPoint;
} ConsoleCoords;

char WeekDays[7][3] = {"Sun", "Mon", 
                       "Tue", "Wed",
                       "Thu", "Fri",
                       "Sat"};

char Months[12][3] = {"Jan", "Feb", "Mar", 
                      "Apr", "May", "Jun", 
                      "Jul", "Aug", "Sep", 
                      "Oct", "Nov", "Dec"};

void runCalendar();
void drawCalendar(WORD wMonth, CursorCoords* cursorCoords);
void drawMonthByDays(short quantityDays, CursorCoords* cursorCoords);
void drawTitleMonth(WORD wMonth);
void drawCurrentDate();
COORD getCoordsToDrawTitleMonth();
COORD getCoordsToDrawDate();
COORD getStartPositionToDraw();
ConsoleCoords getConsoleCoords();
CursorCoords* setCursorPos(CursorCoords* cursorCoords);
void listenToButtonClicks(CursorCoords* cursorCoords);
void moveCursor(CursorCoords* cursorCoords);

void runCalendar()
{
    SYSTEMTIME date = getDate();
    CursorCoords* cursorCoords = malloc(sizeof(CursorCoords));

    drawCalendar(date.wMonth, cursorCoords);
    setCursorPos(cursorCoords);
    listenToButtonClicks(cursorCoords);
}

void drawCalendar(WORD wMonth, CursorCoords* cursorCoords)
{
    drawMonthByDays(getQuantityDaysInMonth(wMonth), cursorCoords);
    drawTitleMonth(wMonth);
    drawCurrentDate();
}

CursorCoords* setCursorPos(CursorCoords* cursorCoords)
{
    SYSTEMTIME date = getDate();
    cursorCoords ->numberCursor = date.wDay;
    cursorCoords ->coordsCursor = cursorCoords -> numbersCoords[date.wDay-1];
    SetConsoleCursorPosition(HStdOut, cursorCoords ->coordsCursor);

    return cursorCoords;
}

void listenToButtonClicks(CursorCoords* cursorCoords)
{
    char c;
    while (c != '.')
    {
        c = getchar();
        if (c == 'w')
        {
            cursorCoords ->numberCursor -= 7;
        }
        else if (c == 'a')
        {
            cursorCoords ->numberCursor--;
        }
        else if (c == 's')
        {
            cursorCoords ->numberCursor += 7;
        }
        else if (c == 'd')
        {
            cursorCoords ->numberCursor++;
        }
        else if (c == '\n')
        {
            getStrNote();
        }
        moveCursor(cursorCoords);
    }
}

void drawMonthByDays(short quantityDays, CursorCoords* cursorCoords)
{
    COORD startPosition = getStartPositionToDraw();
    short startCursorPosX = startPosition.X;
    short i = 0;
    
    for (short rows = 0; rows < 5; ++rows)
    {
        for (short columns = 0; columns < 7; ++columns)
        {
            SetConsoleCursorPosition(HStdOut, startPosition);
            if (i+1 <= quantityDays)
            {
                cursorCoords ->numbersCoords[i].X = startPosition.X;
                cursorCoords ->numbersCoords[i].Y = startPosition.Y;
                printf("%d", i+1);
                ++i;
            }
            startPosition.X += 3;
        }
        startPosition.X = startCursorPosX;
        startPosition.Y += 3;
    }
}

void drawTitleMonth(WORD wMonth)
{
    COORD cursorPos = getCoordsToDrawTitleMonth();
    SetConsoleCursorPosition(HStdOut, cursorPos);

    printf("%c%c%c", Months[wMonth-1][0], Months[wMonth-1][1], Months[wMonth-1][2]);
}

void drawCurrentDate()
{
    SYSTEMTIME date = getDate();
    COORD cursorPos = getCoordsToDrawDate();
    SetConsoleCursorPosition(HStdOut, cursorPos);

    printf("Now:   ");
    printf("%c%c%c | ", Months[date.wMonth-1][0], Months[date.wMonth-1][1], Months[date.wMonth-1][2]);
    printf("%d | ", date.wDay);
    printf("%c%c%c", WeekDays[date.wDayOfWeek][0], WeekDays[date.wDayOfWeek][1], WeekDays[date.wDayOfWeek][2]);
}

void moveCursor(CursorCoords* cursorCoords)
{
    SYSTEMTIME date = getDate();
    short daysInMonth = getQuantityDaysInMonth(date.wMonth);

    printf("%d", cursorCoords ->numberCursor);

    if (cursorCoords ->numberCursor == daysInMonth+1)
    {
        cursorCoords ->numberCursor = 1;
    }
    else if (cursorCoords ->numberCursor == 0)
    {
        cursorCoords ->numberCursor = daysInMonth;
    }

    SetConsoleCursorPosition(HStdOut, cursorCoords ->numbersCoords[cursorCoords ->numberCursor-1]);
}

COORD getCoordsToDrawTitleMonth()
{
    COORD coords = getStartPositionToDraw();
    coords.Y -= 3;
    
    return coords;
}

COORD getCoordsToDrawDate()
{
    COORD coords = getStartPositionToDraw();
    coords.Y += 15;
    return coords;
}

COORD getStartPositionToDraw()
{
    COORD startPos;
    ConsoleCoords consoleCoords = getConsoleCoords();
    startPos.X = ((consoleCoords.rightPoint / 2) / 4);
    short x = (startPos.X / 2) / 4;
    startPos.X += x*3;
    startPos.Y = 8;

    return startPos;
}

ConsoleCoords getConsoleCoords()
{
    ConsoleCoords consoleCoords;
    consoleCoords.leftPoint = CsbInfo.srWindow.Left;
    consoleCoords.rightPoint = CsbInfo.srWindow.Right;
    consoleCoords.topPoint = CsbInfo.srWindow.Top;
    consoleCoords.bottomPoint = CsbInfo.srWindow.Bottom;

    return consoleCoords;
}