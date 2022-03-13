/* @Author: Daniil Maslov */

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "main.h"
#include "daysInMonths.c"
#include "interface.c"
#include "note.c"
#include "calendar.c"


void main()
{   
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdOut, &CsbInfo);
    
    system("cls");
    SetConsoleTitle("Pretty calendar");
    runCalendar();
}