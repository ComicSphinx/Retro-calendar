/* @Author: Daniil Maslov*/

/* TODO:
 * Перерисовывать число при перемещении курсора на него, 
 * но уже другим цветом.
 * Думаю, это будет супер
 * 
 * TODO:
 * Важные дни нужно рисовать отдельным цветом
 */

typedef struct
{
    short left;
    short right;
    short top;
    short bottom;
} ConsoleSize;


HANDLE HStdOut;
CONSOLE_SCREEN_BUFFER_INFO CsbInfo;


void drawCalendar();
COORD getStartPosition();
ConsoleSize getConsoleSize();
void drawMonthByDays(short length, COORD startPosition);

void drawCalendar()
{
    HStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(HStdOut, &CsbInfo);

    SYSTEMTIME date = getDate();
    short numberOfDays = getDaysInCurrentMonthFromFile(date.wMonth);


    COORD startPosition = getStartPosition();
    drawMonthByDays(numberOfDays, startPosition);
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

void drawMonthByDays(short length, COORD cursorPos)
{
    long unsigned int cWrittenChars;
    short startCursorPosX = cursorPos.X;
    short numberOfDay = 1;


    system("cls");

    for (short rows = 0; rows < 6; ++rows)
    {
        for (short columns = 0; columns < 5; ++columns)
        {
            SetConsoleCursorPosition(HStdOut, cursorPos);
            printf("%d", numberOfDay);
            
            ++numberOfDay;
            cursorPos.X += 3;
        }
        cursorPos.X = startCursorPosX;
        cursorPos.Y += 3;
    }
}