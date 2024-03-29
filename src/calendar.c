// @Author: Daniil Maslov

void runCalendar();
CursorCoords* setStartCursorPos(CursorCoords* cursorCoords);
void listenToButtonClicks(CursorCoords* cursorCoords);
void moveCursor(CursorCoords* cursorCoords);

void runCalendar()
{
    CursorCoords* cursorCoords = malloc(sizeof(CursorCoords));

    drawCalendar(cursorCoords);
    setStartCursorPos(cursorCoords);
    listenToButtonClicks(cursorCoords);
}

CursorCoords* setStartCursorPos(CursorCoords* cursorCoords)
{
    SYSTEMTIME date = getDate();
    cursorCoords ->numberCursor = date.wDay;
    cursorCoords ->coordsCursor = cursorCoords -> numbersCoords[date.wDay-1];
    SetConsoleCursorPosition(hStdOut, cursorCoords ->coordsCursor);

    return cursorCoords;
}

void listenToButtonClicks(CursorCoords* cursorCoords)
{
    char c;
    while (c != 'q')
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
        clearStringToGetNote(); // не знаю, почему оно не работает, когда стоит в get note
        moveCursor(cursorCoords);

        // get note
        if(c == 'n')
        {
            int i = 0;
            i = getStrNote();
            if (i == 1)
            {
                moveCursor(cursorCoords);
            }
        }
    }
}

void moveCursor(CursorCoords* cursorCoords)
{
    SYSTEMTIME date = getDate();
    short daysInMonth = getQuantityDaysInMonth(date.wMonth);

    // use when you need to debug
    // it draws current number (where cursor is located)
    // printf("%d", cursorCoords ->numberCursor);

    if (cursorCoords ->numberCursor == daysInMonth+1)
    {
        cursorCoords ->numberCursor = 1;
    }
    else if (cursorCoords ->numberCursor == 0)
    {
        cursorCoords ->numberCursor = daysInMonth;
    }

    drawMonthByDays(getQuantityDaysInMonth(date.wMonth), cursorCoords, date.wDay, cursorCoords ->numberCursor);
    SetConsoleCursorPosition(hStdOut, cursorCoords ->numbersCoords[cursorCoords ->numberCursor-1]);
}