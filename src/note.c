#define FILE_CONTAINS_NOTES "notes.txt"
#define MAX_LENGTH_NOTE 151

bool getStrNote();
void moveCursorToGetNote();
bool saveNoteToFile(char *str);

bool getStrNote()
{
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
}

void moveCursorToGetNote()
{

}

bool saveNoteToFile(char *str)
{
    FILE *file;
    if ((file = fopen(FILE_CONTAINS_NOTES, "ab")) == NULL)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < (MAX_LENGTH_NOTE-1); ++i)
        {
            fprintf(file, "%c", str[i]);
        }
        fprintf(file, "\n");
        fclose(file);
        return true;
    }
}