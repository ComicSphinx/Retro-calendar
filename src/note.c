/* @Author: Daniil Maslov */

#define FILE_NAME_CONTAINS_NOTES "notes.txt"
#define MAX_LENGTH_NOTE 150

void showNote();
char* readNoteFromFile();
void saveNoteToFile(char* note, int length, short day);
void getNoteToCurrentDay(short day);
void moveCursorToGetNote(COORD cursorPos);

void showNote()
{
    char* note;
    if ((note = readNoteFromFile()) != 0)
    {
        printf("%s", note);
    }
    else
    {
        printf("You do not have notes on this day");
    }
}

char* readNoteFromFile()
{
    FILE *file;
    char* note = malloc(MAX_LENGTH_NOTE*sizeof(char));

    if ((file = fopen(FILE_NAME_CONTAINS_NOTES, "r")) == NULL)
    {
        return 0;
    }
    else
    {
        fgets(note, MAX_LENGTH_NOTE, file);
    }

    return note;
}

void saveNoteToFile(char* note, int length, short day)
{
    FILE* file;
    
    if ((file = fopen(FILE_NAME_CONTAINS_NOTES, "ab")) == NULL)
    {
        printf("Can't create or open %s", FILE_NAME_CONTAINS_NOTES);
    }
    else
    {
        for (int j = 0; j < length; ++j)
        {
            fprintf(file, "%c", note[j]);
        }
        fprintf(file, "\n");

        fclose(file);
    }

    free(note);

    
}

void getNoteToCurrentDay(short day)
{
    char c;
    char* noteText = malloc(MAX_LENGTH_NOTE*sizeof(char));
    int counter = 0;

    while (c != '\n' || counter > (MAX_LENGTH_NOTE-1))
    {
        c = getchar();

        noteText[counter] = c;
        ++counter;
    }

    saveNoteToFile(noteText, counter, day);
}

void moveCursorToGetNote(COORD cursorPos)
{
    cursorPos.Y = 2;
    SetConsoleCursorPosition(HStdOut, cursorPos);
}