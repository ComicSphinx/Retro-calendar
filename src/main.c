/* @Author: Daniil Maslov */

#include <windows.h>
#include <stdio.h>
#include <math.h>


#include "daysInEveryMonth.c"
#include "calendar.c"



void main()
{   
    SetConsoleTitle("Pretty calendar");
    runFillDaysInMonths();
    drawCalendar();
}