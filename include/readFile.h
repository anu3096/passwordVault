#include "HashTableAPI.h"

/**Function to read an existing file into the hash table system
 *@pre The hash table exists and has memory allocated to it. The name of the file has been given by the user
 *@param hash table pointer and file name pointer
 *@return pointer to the program password that is stored as the first line inside of the given file
 **/
char * readFile(char *fileName, HTable *hashTable);
