#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Entry {
    char key[50];
    char value[50];
    struct Entry* next;
} Entry;

Entry* hashTable[TABLE_SIZE];

unsigned int hash(const char* key) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue += *key++;
    }
    return hashValue % TABLE_SIZE;
}

void insert(const char* key, const char* value) {
    unsigned int index = hash(key);
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    strcpy(newEntry->key, key);
    strcpy(newEntry->value, value);
    newEntry->next = hashTable[index];
    hashTable[index] = newEntry;
}

const char* get(const char* key) {
    unsigned int index = hash(key);
    Entry* entry = hashTable[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = hashTable[i];
        while (entry) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    insert("name", "Alice");
    insert("age", "25");
    insert("city", "New York");
    
    printf("Name: %s\n", get("name"));
    printf("Age: %s\n", get("age"));
    printf("City: %s\n", get("city"));
    
    freeTable();
    return 0;
}