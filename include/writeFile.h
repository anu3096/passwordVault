#include "HashTableAPI.h"


/**Function to create a new file
 *@pre The name of the file and the program password must be given by the user through input
 *@param name of file, program password
 **/
void createFile(char *fileName, char *programPswd);


/**Function to write the a file
 *@pre The file must exists and the hash table must exists
 *@param  The file name, the system descriptor, the password
 **/
void writeToFile(char *fileName, char *systemDescriptor, char *password);
