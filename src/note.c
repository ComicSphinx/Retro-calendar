#define FILE_CONTAINS_NOTES "notes.txt"
#define MAX_LENGTH_NOTE 151

bool getStrNote();
void moveCursorToGetNote();
bool saveNoteToFile(char *str);
void moveCursorBack(COORD coord);

// void getStrNote()
// {
//     char c;
//     char* noteText = malloc(MAX_LENGTH_NOTE*sizeof(char));
//     int counter = 0;

//     while (c != '\n' || counter > (MAX_LENGTH_NOTE-1))
//     {
//         c = getchar();

//         noteText[counter] = c;
//         ++counter;
//     }
//     saveNoteToFile(noteText);

// }

bool getStrNote(COORD coord)
{   // TODO: оно криво записывает данные в str
    char c;
    char *str = malloc(MAX_LENGTH_NOTE*sizeof(char));
    short counter = 0;

    moveCursorToGetNote();

    if (c != '\n' || counter < (MAX_LENGTH_NOTE-1))
    {
        c = getchar();
        str[counter] = c;
        ++counter;
    }

    if (saveNoteToFile(str))
    {
        return true;
    }
    else
    {
        return false;
    }
    
    moveCursorBack(coord);
}

void moveCursorToGetNote()
{
    COORD coord;
    coord.X = 70;
    coord.Y = 8;
    SetConsoleCursorPosition(HStdOut, coord);
}

bool saveNoteToFile(char *str) // TODO:нужно ли мне bool?
{
    FILE *file;
    if ((file = fopen(FILE_CONTAINS_NOTES, "w")) == NULL) // заменить на a+ / ab, когда эта функция будет работать нормально
    {
        return false;
    }
    else
    {
        // for (int i = 0; i < (MAX_LENGTH_NOTE-1); ++i)
        // {
        //     // fprintf(file, "%c", str[i]);
        // }
        fprintf(file, "%c", str[1]);
        fprintf(file, "\n");
        fclose(file);

        
        return true;
    }
}

void moveCursorBack(COORD coord)
{
    SetConsoleCursorPosition(HStdOut, coord);
}