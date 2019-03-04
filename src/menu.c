#include "HashTableAPI.h"
#include "readFile.h"
#include "writeFile.h"
#include "hashScraping.h"

void menu()
{
    HTable *hashTable;
    char fileName[25];
    char folderDir[35];
    char systemDescriptor[25];
    char passwordChange[25];
    char userProgramPassword[25];
    char userOptionStr[25];
    char saveOption[3];
    char *programPswd;
    void *lookUpPassword;
    int userOption = 0;
    int fileTrip = 0;
    int saveChanges = 0;
    int maxY;
    
    hashTable = createTable(200);
    strcpy(folderDir, "docs/");
    
    initscr();
    cbreak();
    maxY = getmaxy(stdscr);
    
    printw("Welcome to the password vault program!\n\nTo peform an operation, enter the value corresponding to the operations below:\n\n");
    printw("1) Open an existing password file\n");
    printw("2) Create a new password file\n");
    printw("3) Change password for an existing system\n");
    printw("4) Add a new system and password\n");
    printw("5) Retrieve password of an existing system\n");
    printw("6) Remove a system entirely from the password vault\n");
    printw("7) Change the program password\n");
    printw("8) Save changes to file\n");
    printw("9) Quit");
    refresh();
    
    while(userOption != 9)
    {
        mvprintw(maxY-3,0, ">>");
        move(maxY-3,2);
        getstr(userOptionStr);
        userOption = atoi(userOptionStr);
        move(maxY-3,2);
        clrtoeol();
        
        if ((userOption > 0) && (userOption <= 9))
        {
            switch(userOption)
            {
                case(1):
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0, "Enter the name of the file including the extension:>>");
                    getstr(fileName);
                    programPswd = readFile(fileName, hashTable);
                    
                    if (programPswd != NULL)
                    {
                        mvprintw(maxY-2, 0, "File has been read sucessfully (press enter to continue)");
                        fileTrip = 1;
                    }
                    getch();
                    move(maxY-3, 0);
                    clrtoeol();
                    move(maxY-2, 0);
                    clrtoeol();
                    move(maxY-1, 0);
                    clrtoeol();
                    
                    break;
                    
                case(2):
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0, "Enter the name of the file:>>");
                    getstr(fileName);
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0, "Enter a program password:>>");
                    getstr(userProgramPassword);
                    strcat(folderDir, fileName);
                    createFile(folderDir, userProgramPassword);
                    programPswd = readFile(folderDir, hashTable);
                    
                    fileTrip = 1;
                    
                    mvprintw(maxY-2, 0, "File has been created succesfully (press enter to continue)");
                    
                    getch();
                    move(maxY-3, 0);
                    clrtoeol();
                    move(maxY-2, 0);
                    clrtoeol();
                    
                    break;
                    
                case(3):
                    if (fileTrip != 1)
                    {
                        mvprintw(maxY-2, 0, "No file has been read or created yet (press enter to continue)");
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                        
                        break;
                    }
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0, "Enter the program password to make any changes:>>");
                    getstr(userProgramPassword);
                    
                    if (strcmp(userProgramPassword, programPswd) == 0)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-1, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0, "Program Password matched! (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        mvprintw(maxY-3, 0, "Enter the system:>>");
                        getstr(systemDescriptor);
                        move(maxY-3, 0);
                        clrtoeol();
                        mvprintw(maxY-3, 0, "Enter the new password:>>");
                        getstr(passwordChange);
                        lookUpPassword = lookupData(hashTable, systemDescriptor);
                        
                        if (lookUpPassword == NULL)
                        {
                            move(maxY-2, 0);
                            clrtoeol();
                            move(maxY-1, 0);
                            clrtoeol();
                            mvprintw(maxY-2, 0, "System does not exist in file (press enter to continue)");
                            getch();
                            move(maxY-3, 0);
                            clrtoeol();
                            move(maxY-2, 0);
                            clrtoeol();
                            break;
                        }
                        insertData(hashTable, systemDescriptor, passwordChange);
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0, "'%s' has been changed to '%s' for system: %s (press enter)", lookUpPassword, passwordChange, systemDescriptor);
                        saveChanges = 1;
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-1, 0);
                        clrtoeol();
                    }
                    else
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Access Denied! (press enter to continue)");
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                    }
                    
                    break;
                    
                case(4):
                    if (fileTrip != 1)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"No file has been read or created yet (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        break;
                    }
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0,"Enter the program password to make any changes:>>");
                    getstr(userProgramPassword);
                    
                    if (strcmp(userProgramPassword, programPswd) == 0)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Program Password matched! (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        
                        mvprintw(maxY-3, 0,"Enter the system:>>");
                        getstr(systemDescriptor);
                        move(maxY-3, 0);
                        clrtoeol();
                        
                        lookUpPassword = lookupData(hashTable, systemDescriptor);
                        
                        if (lookUpPassword != NULL)
                        {
                            move(maxY-2, 0);
                            clrtoeol();
                            mvprintw(maxY-2, 0,"Error! System already exists in file. (press enter to continue)");
                            getch();
                            move(maxY-2, 0);
                            clrtoeol();
                            move(maxY-3, 0);
                            clrtoeol();
                            
                            break;
                            
                        }
                        
                        mvprintw(maxY-3, 0,"Enter the password:>>");
                        getstr(passwordChange);
                        
                        insertData(hashTable, systemDescriptor, passwordChange);
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"New data has been added! (press enter to continue)");
                        saveChanges = 1;
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        
                    }
                    else
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Access Denied! (press enter to continue)");
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                    }
                    
                    break;
                    
                case(5):
                    if (fileTrip != 1)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"No file has been read or created yet (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        
                        break;
                    }
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0,"Enter the program password to make any changes>>");
                    getstr(userProgramPassword);
                    
                    if (strcmp(userProgramPassword, programPswd) == 0)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Program Password matched! (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        
                        mvprintw(maxY-3, 0,"Enter the system:>>");
                        getstr(systemDescriptor);
                        lookUpPassword = lookupData(hashTable, systemDescriptor);
                        
                        if (lookUpPassword == NULL)
                        {
                            move(maxY-2, 0);
                            clrtoeol();
                            mvprintw(maxY-2, 0, "System does not exist in file (press enter to continue)");
                            getch();
                            move(maxY-3, 0);
                            clrtoeol();
                            move(maxY-2, 0);
                            clrtoeol();
                            break;
                        }
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"'%s' is the password for the system: %s (press enter to continue)", lookUpPassword,systemDescriptor);
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-1, 0);
                        clrtoeol();
                        
                    }
                    else
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Access Denied! (press enter to continue)");
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                    }
                    
                    break;
                    
                case(6):
                    if (fileTrip != 1)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"No file has been read or created yet (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        
                        break;
                    }
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0,"Enter the program password to make any changes>>");
                    getstr(userProgramPassword);
                    
                    if (strcmp(userProgramPassword, programPswd) == 0)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Program Password matched! (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        
                        
                        mvprintw(maxY-3, 0,"Enter the system you wish to delete>>");
                        getstr(systemDescriptor);
                        removeData(hashTable, systemDescriptor);
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"System deleted successfully (press enter to continue)");
                        saveChanges = 1;
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                        
                    }
                    else
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Access Denied! (press enter to continue)");
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                    }
                    break;
                    
                case(7):
                    if (fileTrip != 1)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"No file has been read or created yet (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        
                        break;
                    }
                    move(maxY-3, 0);
                    clrtoeol();
                    mvprintw(maxY-3, 0,"Enter the program password to make any changes>>");
                    getstr(userProgramPassword);
                    
                    if (strcmp(userProgramPassword, programPswd) == 0)
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Program Password matched! (press enter to continue)");
                        getch();
                        move(maxY-2, 0);
                        clrtoeol();
                        move(maxY-3, 0);
                        clrtoeol();
                        
                        mvprintw(maxY-3, 0,"Enter the new program password>>");
                        getstr(userProgramPassword);
                        move(maxY-3, 0);
                        clrtoeol();
                        strcpy(programPswd, userProgramPassword);
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Program password has been changed successfully! (press enter to continue)");
                        saveChanges = 1;
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                    }
                    else
                    {
                        move(maxY-2, 0);
                        clrtoeol();
                        mvprintw(maxY-2, 0,"Access Denied! (press enter to continue)");
                        getch();
                        move(maxY-3, 0);
                        clrtoeol();
                        move(maxY-2, 0);
                        clrtoeol();
                    }
                    break;
                    
                case(8):
                    if (fileTrip == 1)
                    {
                        scrapTable(hashTable, fileName, programPswd);
                    }
                    move(maxY-2, 0);
                    clrtoeol();
                    mvprintw(maxY-2, 0,"Changes have been saved to %s! (press enter to continue)", fileName);
                    getch();
                    move(maxY-3, 0);
                    clrtoeol();
                    move(maxY-2, 0);
                    clrtoeol();
                    
                    break;
                    
                default:
                    if (fileTrip == 1 && saveChanges == 1)
                    {
                        move(maxY-3, 0);
                        clrtoeol();
                        mvprintw(maxY-3, 0,"Would you like to save your changes to '%s'? (choose Y or N):>>", fileName);
                        getstr(saveOption);
                        if ((strcmp(saveOption, "Y") == 0) || strcmp(saveOption, "y") == 0)
                        {
                            scrapTable(hashTable, fileName, programPswd);
                            move(maxY-2, 0);
                            clrtoeol();
                            mvprintw(maxY-2, 0,"Changes have been saved to %s! (press enter to exit)", fileName);
                            getch();
                            move(maxY-3, 0);
                            clrtoeol();
                            move(maxY-2, 0);
                            clrtoeol();
                        }
                    }
                    free(hashTable);
                    break;
            }
        }
        else
        {
            move(maxY-2, 0);
            clrtoeol();
            mvprintw(maxY-2, 0,"Please enter a value that is between 1 and 9 (please enter to continue)");
            getch();
            move(maxY-3, 0);
            clrtoeol();
            move(maxY-2, 0);
            clrtoeol();
        }
    }
    endwin();
    
}



