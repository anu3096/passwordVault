#include "hashScraping.h"

void scrapTable(HTable *hashTable, char *fileName, char *programPswd)
{
    Vault *tempData;
    Node *searchNode;
    int i;
    
    if (hashTable == NULL)
        return;
    
    createFile(fileName, programPswd);
    
    for (i = 0; i < hashTable->size; i++)
    {
        if (hashTable->table[i] != NULL)
        {
            tempData = (Vault*)(hashTable->table[i]->data);
            writeToFile(fileName, tempData->systemDescriptor, tempData->password);
            
            searchNode = hashTable->table[i]->next;
            while(searchNode != NULL)
            {
                tempData = (Vault*)(searchNode->data);
                writeToFile(fileName, tempData->systemDescriptor, tempData->password);
                
                searchNode = searchNode->next;
            }
        }
    }
}
