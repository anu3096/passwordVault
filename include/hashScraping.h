#include "writeFile.h"
#include "HashTableAPI.h"

/**Function to search the hash table and find where systems and passwords are saved
 *@pre The hash table exists and has memory allocated to it. File name must exist. Program password must exist.
 *@param hashTable pointer to the hash table, name of the file, program password
 **/
void scrapTable(HTable *hashTable, char *fileName, char *programPswd);
