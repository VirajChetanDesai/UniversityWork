#define TABLE_SIZE 1000

enum TokenType {
    STRING_LITERAL,
    RELATIONAL_OPERATOR,
    ASSIGNMENT_OPERATOR,
    ARITHMETIC_OPERATOR,
    LOGICAL_OPERATOR,
    INVALID_OPERATOR,
    KEYWORD,
    IDENTIFIER,
    FUNCTION,
    SPECIAL_SYMBOL
};

typedef struct HashEntry {
    char* name;
    int index;
    char* type;
    char* scope;
    char* arguments;
    char* numberOfArguments;
    char* returnType;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    HashEntry* table[TABLE_SIZE];
    int index ;
} HashTable;

unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->index = 0;
    if (ht) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            ht->table[i] = NULL;
        }
    }
    return ht;
}

void insert(HashTable* ht, const char* key, int index, const char* type,
            const char* scope, const char* arguments, const char* numberOfArguments,
            const char* returnType) {
    unsigned int hash = hashFunction(key);

    HashEntry* entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (entry) {
        entry->name = strdup(key);
        entry->index = index;
        entry->type = strdup(type);
        entry->scope = strdup(scope);
        entry->arguments = strdup(arguments);
        entry->numberOfArguments = strdup(numberOfArguments);
        entry->returnType = strdup(returnType);
        entry->next = ht->table[hash];
        ht->table[hash] = entry;
    }
    ht->index++;
}

HashEntry* lookup(const HashTable* ht, const char* key) {
    unsigned int hash = hashFunction(key);
    HashEntry* entry = ht->table[hash];
    while (entry != NULL) {
        if (strcmp(entry->name, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }

    return NULL;
}

void cleanupHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashEntry* entry = ht->table[i];
        while (entry != NULL) {
            HashEntry* next = entry->next;
            free(entry->name);
            free(entry->scope);
            free(entry->arguments);
            free(entry->numberOfArguments);
            free(entry->returnType);
            free(entry);
            entry = next;
        }
    }
    free(ht);
}


void printHashTable(const HashTable* ht) {
    printf("--------------------------------------------------------\n");
    printf("| Name               | Index | Type       | Return     |\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashEntry* entry = ht->table[i];
        while (entry != NULL) {
            printf("| %-20s | %-5d | %-10s | %-10s |\n",
                   entry->name, entry->index, entry->type, entry->returnType);
            entry = entry->next;
        }
    }
    printf("--------------------------------------------------------\n");
}



void printToken(const char* tokenType, const char* tokenName, int index, unsigned int row, unsigned int col) {
    printf("<%s,%d,%u,%u,%s>\n", tokenType, index, row, col, tokenName);
}


bool checkKeyword(char *input_word) {
    if (strcmp(input_word, "auto") == 0 ||
        strcmp(input_word, "break") == 0 ||
        strcmp(input_word, "case") == 0 ||
        strcmp(input_word, "char") == 0 ||
        strcmp(input_word, "const") == 0 ||
        strcmp(input_word, "continue") == 0 ||
        strcmp(input_word, "default") == 0 ||
        strcmp(input_word, "do") == 0 ||
        strcmp(input_word, "double") == 0 ||
        strcmp(input_word, "else") == 0 ||
        strcmp(input_word, "enum") == 0 ||
        strcmp(input_word, "extern") == 0 ||
        strcmp(input_word, "float") == 0 ||
        strcmp(input_word, "for") == 0 ||
        strcmp(input_word, "goto") == 0 ||
        strcmp(input_word, "if") == 0 ||
        strcmp(input_word, "int") == 0 ||
        strcmp(input_word, "long") == 0 ||
        strcmp(input_word, "register") == 0 ||
        strcmp(input_word, "return") == 0 ||
        strcmp(input_word, "short") == 0 ||
        strcmp(input_word, "signed") == 0 ||
        strcmp(input_word, "sizeof") == 0 ||
        strcmp(input_word, "static") == 0 ||
        strcmp(input_word, "struct") == 0 ||
        strcmp(input_word, "switch") == 0 ||
        strcmp(input_word, "typedef") == 0 ||
        strcmp(input_word, "union") == 0 ||
        strcmp(input_word, "unsigned") == 0 ||
        strcmp(input_word, "void") == 0 ||
        strcmp(input_word, "volatile") == 0 ||
        strcmp(input_word, "while") == 0) {
        return true;
    } else {
        return false;
    }
}

void removeCommentsAndDirectives(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening files");
        return;
    }

    int insideSingleLineComment = 0;
    int insideMultiLineComment = 0;
    int insideString = 0;
    char prevChar = '\0';
    char currentChar;

    while ((currentChar = fgetc(inputFile)) != EOF) {
        if (insideMultiLineComment) {
            if (prevChar == '*' && currentChar == '/') {
                insideMultiLineComment = 0;
                prevChar = '\0';
                continue;
            }
        } else if (insideSingleLineComment) {
            if (currentChar == '\n') {
                insideSingleLineComment = 0;
            }
        } else {
            if (currentChar == '"' && prevChar != '\\') {
                insideString = !insideString;
            } else if (!insideString) {
                if (currentChar == '/' && prevChar == '/') {
                    insideSingleLineComment = 1;
                    fseek(outputFile,-1,SEEK_CUR);
                    fputc(' ', outputFile); 
                } else if (currentChar == '/' && prevChar == '*') {
                    insideMultiLineComment = 1;
                } else if (currentChar == '#') {
                    // Skip the entire directive line
                    insideSingleLineComment = 1;
                } else {
                    fputc(currentChar, outputFile);
                }
            }
        }

        prevChar = currentChar;
    }

    fclose(inputFile);
    fclose(outputFile);
}