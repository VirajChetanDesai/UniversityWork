#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 1000

typedef struct HashEntry {
    char* verb;
    struct HashEntry* next;
} HashEntry;

typedef struct HashTable {
    HashEntry* table[TABLE_SIZE];
    int prevHashes[TABLE_SIZE];
    int index;
} HashTable;

int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht) {
        ht->index = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            ht->prevHashes[i] = -1;
            ht->table[i] = NULL;
        }
    }
    return ht;
}

void push(HashTable* ht, const char* key) {
    unsigned int hash = hashFunction(key);
    if (ht->index == TABLE_SIZE - 1) {
        printf("Table is full");
        return;
    }
    HashEntry* he = (HashEntry*)malloc(sizeof(HashEntry));
    if (he) {
        he->verb = strdup(key);
        he->next = NULL;
        if (ht->table[hash] == NULL) {
            ht->table[hash] = he; 
        } else {
            HashEntry* current = ht->table[hash];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = he;
        }

        ht->prevHashes[ht->index++] = hash;
    }
}


HashEntry* lookup(HashTable* ht, const char* key) {
    unsigned int hash = hashFunction(key);
    HashEntry* current = ht->table[hash];
    while (current != NULL) {
        if (strcmp(current->verb, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Enter the correct input");
        exit(1);
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("No access to the given file");
        exit(1);
    }

    HashTable* ht = createHashTable();
    char line[100]; 
    while (fgets(line, sizeof(line), fp)) {
        push(ht, line);
    }
    fclose(fp);
    return 0;
}
