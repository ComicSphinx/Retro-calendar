// @Author: Daniil Maslov

char Months[12][3] = {"Jan", "Feb", "Mar", 
                      "Apr", "May", "Jun", 
                      "Jul", "Aug", "Sep", 
                      "Oct", "Nov", "Dec"};

char WeekDays[7][3] = {"Sun", "Mon", 
                       "Tue", "Wed",
                       "Thu", "Fri",
                       "Sat"};

void drawCalendar(CursorCoords* cursorCoords);
void drawMonthByDays(short quantityDays, CursorCoords* cursorCoords, short currentDayOfMonth);
void drawTitleMonth(WORD wMonth);
void drawCurrentDate(SYSTEMTIME date);
void drawSeparator();
COORD getCoordsToDrawTitleMonth();
COORD getCoordsToDrawDate();
COORD getStartPositionToDraw();
short getTopCoord();
short getBottomCoord();
COORD getStartPositionOfSeparator();
ConsoleCoords getConsoleCoords();

void drawCalendar(CursorCoords* cursorCoords)
{
    SYSTEMTIME date = getDate();

    drawMonthByDays(getQuantityDaysInMonth(date.wMonth), cursorCoords, date.wDay);
    drawTitleMonth(date.wMonth); // TODO: мб из date получать?
    drawCurrentDate(date);
    drawSeparator();
}

void drawMonthByDays(short quantityDays, CursorCoords* cursorCoords, short currentDayOfMonth) // получать текущий день, и if i = today do print with color SetConsoleTextAttribute(hStdOut, 2);
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // # TODO надо бы в drawCalendar вынести на всякий
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
                if (i+1 == currentDayOfMonth)
                {
                    SetConsoleTextAttribute(hStdOut, 2);
                }
                cursorCoords ->numbersCoords[i].X = startPosition.X;
                cursorCoords ->numbersCoords[i].Y = startPosition.Y;
                printf("%d", i+1);
                ++i;
                SetConsoleTextAttribute(hStdOut, 7);
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

void drawCurrentDate(SYSTEMTIME date)
{
    COORD cursorPos = getCoordsToDrawDate();
    SetConsoleCursorPosition(HStdOut, cursorPos);

    printf("Now:   ");
    printf("%c%c%c | ", Months[date.wMonth-1][0], Months[date.wMonth-1][1], Months[date.wMonth-1][2]);
    printf("%d | ", date.wDay);
    printf("%c%c%c", WeekDays[date.wDayOfWeek][0], WeekDays[date.wDayOfWeek][1], WeekDays[date.wDayOfWeek][2]);
}

void drawSeparator()
{
    COORD cursorPos = getStartPositionOfSeparator();
    SetConsoleCursorPosition(HStdOut, cursorPos);
    ConsoleCoords consoleCoords = getConsoleCoords();

    while (cursorPos.Y < getBottomCoord())
    {
        printf("|");
        cursorPos.Y += 1;
        SetConsoleCursorPosition(HStdOut, cursorPos);
    }

}

COORD getCoordsToDrawTitleMonth()
{
    COORD coords = getStartPositionToDraw();
    coords.Y = getTopCoord() - 3;
    
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
    startPos.Y = getTopCoord();

    return startPos;
}

short getTopCoord()
{
    return 8;
}

short getBottomCoord()
{
    ConsoleCoords consoleCoords = getConsoleCoords();
    return (consoleCoords.bottomPoint-5);
}

COORD getStartPositionOfSeparator()
{
    COORD startPos = getCoordsToDrawTitleMonth();
    ConsoleCoords consoleCoords = getConsoleCoords();
    
    startPos.X = (consoleCoords.rightPoint / 2);

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