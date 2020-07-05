/* @Author: Daniil Maslov */

#include <windows.h>
#include <stdio.h>
#include <math.h>


#include "daysInEveryMonth.c"
#include "note.c"
#include "calendar.c"


void main()
{   
    SYSTEMTIME date = getDate();
    
    SetConsoleTitle("Pretty calendar");
    
    runFillDaysInMonths();
    drawCalendar();
    drawNowDate();
    drawTitleMonth(date.wMonth);
    moveCursor();
}