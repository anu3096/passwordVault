#include "HashTableAPI.h"


HTable *createTable(size_t size)
{
    HTable *hashTable;
    int i;

    if (size < 1)
    {
        return NULL;
    }

    hashTable = (HTable*)malloc(sizeof(HTable));
    hashTable->table = (Node**)malloc(sizeof(Node)*size);

    for (i = 0; i < size; i++)
    {
        hashTable->table[i] = NULL;
    }
    
    hashTable->size = size;
    
    return hashTable;
}


Node *createNode(char *systemDescriptor, char *password)
{
    
    Node *newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = initializeData(systemDescriptor, password);
    newNode->next = NULL;

    return newNode;
}

void *initializeData(char *systemDescriptor, char *password)
{
    void *temp;
    
    temp = (Vault*)malloc(sizeof(Vault));
    
    strcpy(((Vault*)temp)->systemDescriptor, systemDescriptor);
    strcpy(((Vault*)temp)->password, password);
    
    return temp;
}

void destroyTable(HTable *hashTable)
{
    Node *temp;
    Node *tempNext;
    Node *deleteNode;
    int i = 0;

    if (hashTable == NULL)
        return;

    while(hashTable->table[i] != NULL)
    {
        temp = hashTable->table[i];
        tempNext = temp->next;
        i++;

        free(((Vault*)temp)->password);

        while(tempNext != NULL)
        {
            deleteNode = tempNext;
            tempNext = tempNext->next;
            free(deleteNode);
        }

        free(temp);        
    }

}


void insertData(HTable *hashTable, char *systemDescriptor, char *password)
{
    if (hashTable != NULL)
    {
        Node *insertNode = createNode(systemDescriptor, password);
        int index = hashFunction(hashTable->size, systemDescriptor);
        if (hashTable->table[index] != NULL)
        {
            Vault *tempData = (Vault*)(hashTable->table[index]->data);
            if ((strcmp(tempData->systemDescriptor, systemDescriptor)) == 0)
            {
                insertNode->next = hashTable->table[index]->next;
                hashTable->table[index] = insertNode;
            }
            else
            {
                Node *temp = hashTable->table[index];
                while(temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = insertNode;
            }
        }
        else
        {
            hashTable->table[index] = insertNode;
        }
    }
}


void removeData(HTable *hashTable, char *systemDescriptor)
{
    Node *removeNode;
    
    if (hashTable != NULL)
    {
        int index = hashFunction(hashTable->size, systemDescriptor);
        
        if (hashTable->table[index] != NULL)
        {
            removeNode = hashTable->table[index];
            Vault *tempData = (Vault*)(hashTable->table[index]->data);
            Node *previous = NULL;
            
            while((strcmp(tempData->systemDescriptor, systemDescriptor)) != 0)
            {
                previous = removeNode;
                removeNode = removeNode->next;
            }
            
            if ((strcmp(tempData->systemDescriptor, systemDescriptor)) == 0)
            {
                if (previous == NULL)
                {
                    hashTable->table[index] = removeNode->next;
                    free(removeNode);
                    
                }
                else
                {
                    previous->next = removeNode->next;
                    free(removeNode);
                }
            }
        }
    }

}

void *lookupData(HTable *hashTable, char *systemDescriptor)
{
    HTable *tempTable;
    Node *lookupNode;
    
    tempTable = hashTable;
    
    if (tempTable != NULL)
    {
        int index = hashFunction(tempTable->size, systemDescriptor);
        
        if (tempTable->table[index] == NULL)
        {
            return NULL;
        }
        
        lookupNode = tempTable->table[index];
        while(lookupNode != NULL)
        {
            Vault *tempData = (Vault*)(lookupNode->data);
            if ((strcmp(tempData->systemDescriptor, systemDescriptor)) == 0)
            {
                return tempData->password;
            }
            
            lookupNode = lookupNode->next;
        }
    }
    return NULL;
}

int hashFunction(size_t size, char *systemDescriptor)
{
    int index = 0;
    
    index = (strlen(systemDescriptor)) % size;
    return index;
}




