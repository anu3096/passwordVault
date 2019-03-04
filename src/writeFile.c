#include "writeFile.h"

void createFile(char *fileName, char *programPswd)
{
    FILE *outputFile;
    
    outputFile = fopen(fileName, "w");
    
    strcat(programPswd, "\n");
    
    fputs(programPswd, outputFile);
    
    fclose(outputFile);
    
}

void writeToFile(char *fileName, char *systemDescriptor, char *password)
{
    FILE *outputFile;
    
    outputFile = fopen(fileName, "a");
    
    strcat(systemDescriptor, " ");
    strcat(password, "\n");
    
    fputs(systemDescriptor, outputFile);
    fputs(password, outputFile);
    
    fclose(outputFile);
}
