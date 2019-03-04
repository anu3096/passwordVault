#include "readFile.h"

char * readFile(char *fileName, HTable *hashTable)
{
    FILE *inputFile;
    char buffer[150];
    char systemDescriptor[25];
    char password[25];
    char *programPswd = malloc(sizeof(char)*25);
    int iteration = 0;
    int maxY = 0;
    
    inputFile = fopen(fileName, "r");
    maxY = getmaxy(stdscr);
    
    if (inputFile == NULL)
    {
        mvprintw(maxY-2, 0, "Error when reading the file (press enter to continue)");
        free(programPswd);
        return NULL;
    }
    
    while(fgets(buffer, 150, inputFile) != NULL)
    {
        if (iteration > 0)
        {
            strcpy(systemDescriptor, strtok(buffer, " "));
            strcpy(password, strtok(NULL, "\n"));
            insertData(hashTable, systemDescriptor, password);
        }
        else
        {
            strcpy(programPswd, strtok(buffer, "\n"));
        }
        iteration++;
    }
    
    fclose(inputFile);
    return programPswd;
}

