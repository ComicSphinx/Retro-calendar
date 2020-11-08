#define FILE_CONTAINS_NOTES "notes.txt"
#define MAX_LENGTH_NOTE 151

void getStrNote();
void prepareStrToGetData(char *str);
void moveCursorToGetNote();
void saveNoteToFile(char *str);
void moveCursorBack(COORD coord);

void getStrNote(COORD coord)
{
    char c = ' ';
    char *str = malloc(MAX_LENGTH_NOTE*sizeof(char));
    short counter = 0;

    prepareStrToGetData(str);
    moveCursorToGetNote();

    while (c != '\n' || counter > (MAX_LENGTH_NOTE-1))
    {
        c = getchar();
        str[counter] = c;
        ++counter;
    }
    saveNoteToFile(str);
    moveCursorBack(coord);
}

void prepareStrToGetData(char *str)
{
    for (int i = 0; i < MAX_LENGTH_NOTE; ++i)
    {
        str[i] = ' ';
    }
}

void moveCursorToGetNote()
{
    COORD coord;
    coord.X = 70;
    coord.Y = 8;
    SetConsoleCursorPosition(HStdOut, coord);
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

void moveCursorBack(COORD coord)
{
    SetConsoleCursorPosition(HStdOut, coord);
}