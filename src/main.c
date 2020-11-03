/* @Author: Daniil Maslov */

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "main.h"
#include "daysInMonths.c"
#include "note.c"
#include "calendar.c"

void main()
{   
    HStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(HStdOut, &CsbInfo);
    
    system("cls");
    SetConsoleTitle("Pretty calendar");
    runCalendar();
}