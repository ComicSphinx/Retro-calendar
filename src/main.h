// Author: Daniil Maslov

HANDLE hStdOut;
CONSOLE_SCREEN_BUFFER_INFO CsbInfo;

typedef struct
{
    short numberCursor;
    COORD numbersCoords[32];
    COORD coordsCursor;
} CursorCoords;

typedef struct
{
    short leftPoint;
    short rightPoint;
    short topPoint;
    short bottomPoint;
} ConsoleCoords;