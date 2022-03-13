// Author: Daniil Maslov

#define FILE_CONTAINS_NOTES "notes.txt"
#define MAX_LENGTH_NOTE 151

short getStrNote();
void prepareStrToGetData(char *str);
void saveNoteToFile(char *str);
void drawMessageToGetNote();
void clearStringToGetNote();

short getStrNote()
{
    char c = ' ';
    char *str = malloc(MAX_LENGTH_NOTE*sizeof(char));
    short counter = 0;

    prepareStrToGetData(str);
    drawMessageToGetNote();

    while (c != '\n' || counter > (MAX_LENGTH_NOTE-1))
    {
        c = getchar();
        str[counter] = c;
        ++counter;
    }
    saveNoteToFile(str);
    
    if (counter > 1)
    {
        return 1;
    }
}

void prepareStrToGetData(char *str)
{
    for (int i = 0; i < MAX_LENGTH_NOTE; ++i)
    {
        str[i] = ' ';
    }
}

void saveNoteToFile(char *str)
{
    FILE *file;
    if ((file = fopen(FILE_CONTAINS_NOTES, "a+")) == NULL) // заменить на a+ / ab, когда эта функция будет работать нормально
    {
        // тут надо как-то отработать
    }
    else
    {
        for (int i = 0; i < (MAX_LENGTH_NOTE-1); ++i)
        {
            fprintf(file, "%c", str[i]); // TODO: пишет только нулевой символ, но не последующие
        }
        // fprintf(file, "\n"); нужно ли? a+ должно самостоятельно добавлять строку
        fclose(file);
    }
}

void drawMessageToGetNote()
{
    // надо будет как-то искореннить эти магические числа
    COORD coord;
    coord.X = 62;
    coord.Y = 23;
    SetConsoleCursorPosition(hStdOut, coord);
    printf(">> ");
}

void clearStringToGetNote()
{
    COORD coord;
    coord.X = 62;
    coord.Y = 23;
    // clear
    SetConsoleCursorPosition(hStdOut, coord);
    printf("                                 ");
}