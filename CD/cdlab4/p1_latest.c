#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TABLE_SIZE 1000

enum TokenType {
    STRING_LITERAL,
    RELATIONAL_OPERATOR,
    ASSIGNMENT_OPERATOR,
    ARITHMETIC_OPERATOR,
    LOGICAL_OPERATOR,
    INVALID_OPERATOR,
    KEYWORD,
    FUNCTION,
    IDENTIFIER
};

typedef struct HashEntry {
    char* name;
    int index;
    char* type;
    char* scope;
    char* arguments;
    char* returnType;
    struct HashEntry* next;
    int numArguments; 
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
            const char* scope, const char* arguments,
            const char* returnType, int numArgs) { // Add numArgs parameter
    unsigned int hash = hashFunction(key);

    HashEntry* entry = (HashEntry*)malloc(sizeof(HashEntry));
    if (entry) {
        entry->name = strdup(key);
        entry->index = index;
        entry->type = strdup(type);
        entry->scope = strdup(scope);
        entry->arguments = strdup(arguments);
        entry->returnType = strdup(returnType);
        entry->numArguments = numArgs; // Store the number of arguments
        entry->next = ht->table[hash];
        ht->table[hash] = entry;
    }
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
            free(entry->returnType);
            free(entry);
            entry = next;
        }
    }
    free(ht);
}


void printToken(const char* tokenType, const char* tokenName, int index, unsigned int row, unsigned int col) {
    printf("<%s,%d,%u,%u>%s\n", tokenType, index, row, col, tokenName);
}

void processToken(const char* tokenName, enum TokenType tokenType, unsigned int row, unsigned int col, HashTable* Hashtable) {
    const char* typeString = NULL;
    HashEntry* entry = lookup(Hashtable, tokenName);
    if (entry != NULL) {
        printToken(entry->type, entry->name, entry->index, row, col);
        return;
    }
    if (tokenType == IDENTIFIER && isalpha(tokenName[0]) && strchr(tokenName, '(') != NULL) {
            const char* openingBracket = strchr(tokenName, '(');
            const char* closingBracket = strrchr(tokenName, ')');
            const char* returnType = tokenName; 
            if (openingBracket != NULL) {
                returnType = tokenName;
                while (returnType < openingBracket) {
                    if (*returnType == ' ') {
                        returnType++; 
                    } else {
                        break;
                    }
                }
            }
            if (openingBracket != NULL && closingBracket != NULL && strchr(openingBracket, '"') == NULL) {
                int numArgs = 0;
                const char* comma = openingBracket;
                while (comma < closingBracket) {
                    comma = strchr(comma, ',');
                    if (comma != NULL) {
                    numArgs++;
                    comma++;
                }
            }
            insert(Hashtable, tokenName, Hashtable->index++, "function", "", "", returnType, numArgs);
            printToken("function", tokenName, 0, row, col);
            return;
        }
    }
        
    switch (tokenType) {
        case STRING_LITERAL:
            typeString = "string";
            break;
        case RELATIONAL_OPERATOR:
            typeString = "relational";
            break;
        case ASSIGNMENT_OPERATOR:
            typeString = "assignment";
            break;
        case ARITHMETIC_OPERATOR:
            typeString = "arithmetic";
            break;
        case LOGICAL_OPERATOR:
            typeString = "logical";
            break;
        case INVALID_OPERATOR:
            typeString = "invalid";
            break;
        case KEYWORD:
            typeString = "keyword";
            break;
        case IDENTIFIER:
            typeString = "id";
            break;
    }

    if (typeString != NULL) {
        printToken(typeString, tokenName, 0, row, col);
        insert(Hashtable, tokenName, Hashtable->index++, typeString, "", "", "", "", 0);
    }
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

void removeCommentsAndDirectives(const char* inputFileName, const char* outputFileName) {
    FILE *srcFile, *tgtFile;
    srcFile = fopen(inputFileName, "r");
    if (srcFile == NULL) {
        printf("Input file cannot be opened\n");
        exit(1);
    }
    tgtFile = fopen(outputFileName, "w+");
    if (tgtFile == NULL) {
        printf("Output file cannot be opened\n");
        fclose(srcFile);
        exit(1);
    }
    char c, prev = '\0', prevPrev = '\0';
    int insideString = 0;
    int insideCharLiteral = 0;
    int insideCommentSingle = 0;
    int insideCommentMulti = 0;
    int insideDirective = 0;
    while ((c = fgetc(srcFile)) != EOF) {
        if (!insideCharLiteral && !insideCommentSingle && !insideCommentMulti && !insideDirective) {
            if (c == '"' && prev != '\\' && !insideCommentMulti) {
                insideString = !insideString;
            } else if (c == '\'' && prev != '\\') {
                insideCharLiteral = !insideCharLiteral;
            } else if (c == '/' && prev == '/') {
                insideCommentSingle = 1;
            } else if (c == '*' && prev == '/') {
                insideCommentMulti = 1;
            } else if (c == '#') {
                insideDirective = 1;
            }
            if (!insideString && !insideCharLiteral && !insideDirective) {
                fputc(c, tgtFile);
            }
        } else if (insideCommentSingle && c == '\n') {
            insideCommentSingle = 0;
        } else if (insideCommentMulti && c == '/' && prev == '*') {
            insideCommentMulti = 0;
            continue;
        } else if (insideDirective && c == '\n') {
            insideDirective = 0;
        }

        if (insideString || insideCharLiteral) {
            fputc(c, tgtFile);
        }

        prevPrev = prev;
        prev = c;
    }
    fclose(srcFile);
    fclose(tgtFile);
}

void lexicalAnalyser(const char* outputFileName, HashTable* Hashtable) {
    char c;
    char buf[5000];
    int row = 1, col = 1;
    FILE* fp = fopen(outputFileName, "r");
    
    if (fp == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }
    
    while ((c = fgetc(fp)) != EOF) {
        int i = 0;
        buf[0] = '\0';
        
        if (c == '\n') {
            row++;
            col = 1;
        } else {
            col++;
        }
        
        if (c == '"' || c == '\'') { // Strings or character literals
            char opening_quote = c;
            buf[i++] = c;
            
            while ((c = fgetc(fp)) != EOF) {
                if (c == '\\') { // Escape sequence
                    buf[i++] = c;
                    c = fgetc(fp);
                    buf[i++] = c;
                } else if (c == opening_quote) {
                    buf[i++] = c;
                    buf[i] = '\0';
                    HashEntry* entry = lookup(Hashtable, buf);
                    if (entry != NULL) {
                        printToken(entry->type, entry->name, entry->index, row, col);
                    } else {
                        processToken(buf, STRING_LITERAL, row, col, Hashtable);
                    }
                    break;
                } else {
                    buf[i++] = c;
                }
            }
            
            if (c == EOF) {
                printf("Unclosed string or character literal at row %d, column %d\n", row, col);
                // Handle unclosed string or character literal
            }
        }  else if (c == '=') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=') {
                buf[i++] = c;
                buf[i] = '\0';
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken(entry->type, entry->name, entry->index, row, col);
                } else {
                    processToken(buf, RELATIONAL_OPERATOR, row, col, Hashtable);
                }
            } else {
                buf[i] = '\0';
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken(entry->type, entry->name, entry->index, row, col);
                } else {
                    processToken(buf, ASSIGNMENT_OPERATOR, row, col, Hashtable);
                }
                fseek(fp, -1, SEEK_CUR);
            } 
        } else if (c == '<' || c == '>' || c == '!') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=') {
                buf[i++] = c;
                buf[i] = '\0';
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken(entry->type, entry->name, entry->index, row, col);
                } else {
                    processToken(buf, RELATIONAL_OPERATOR, row, col, Hashtable);
                }
            } else {
                buf[i] = '\0';
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken(entry->type, entry->name, entry->index, row, col);
                } else {
                    processToken(buf, RELATIONAL_OPERATOR, row, col, Hashtable);
                }
                fseek(fp, -1, SEEK_CUR);
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            buf[i++] = c;
            buf[i] = '\0';
            HashEntry* entry = lookup(Hashtable, buf);
            if (entry != NULL) {
                printToken(entry->type, entry->name, entry->index, row, col);
            } else {
                processToken(buf, ARITHMETIC_OPERATOR, row, col, Hashtable);
            }
        } else if (c == '&' || c == '|') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == buf[0]) {
                buf[i++] = c;
                buf[i] = '\0';
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken(entry->type, entry->name, entry->index, row, col);
                } else {
                    processToken(buf, LOGICAL_OPERATOR, row, col, Hashtable);
                }
            } else {
                buf[i] = '\0';
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken(entry->type, entry->name, entry->index, row, col);
                } else {
                    processToken(buf, INVALID_OPERATOR, row, col, Hashtable);
                }
                fseek(fp, -1, SEEK_CUR);
            }
        }else if (isalpha(c) || c == '_') {
    while (isalnum(c) || c == '_') {
        buf[i++] = c;
        c = fgetc(fp);
    }
    buf[i] = '\0';

    if (checkKeyword(buf)) {
        HashEntry* entry = lookup(Hashtable, buf);
        if (entry != NULL) {
            printToken(entry->type, entry->name, entry->index, row, col);
        } else {
            processToken(buf, KEYWORD, row, col, Hashtable);
        }
    } else if (c == '(') {
        HashEntry* entry = lookup(Hashtable, buf);
        if (entry != NULL && strcmp(entry->type, "function") == 0) {
            printToken(entry->type, entry->name, entry->index, row, col);
        } else {
            processToken(buf, IDENTIFIER, row, col, Hashtable);
        }
        fseek(fp, -1, SEEK_CUR);
    } else {
        HashEntry* entry = lookup(Hashtable, buf);
        if (entry != NULL) {
            printToken(entry->type, entry->name, entry->index, row, col);
        } else {
            processToken(buf, IDENTIFIER, row, col, Hashtable);
        }
    }
    fseek(fp, -1, SEEK_CUR);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Enter correct number of inputs\n");
        exit(1);
    }
    char* inputFileName = argv[1];
    char* outputFileName = malloc(strlen(inputFileName) + 5);
    if (outputFileName == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(outputFileName, inputFileName);
    char* extension = strrchr(outputFileName, '.');
    if (extension != NULL) {
        *extension = '\0';
    }
    strcat(outputFileName, ".out");
    HashTable *Hashtable = createHashTable(); 
    removeCommentsAndDirectives(inputFileName, outputFileName);
    lexicalAnalyser(outputFileName, Hashtable); 
    cleanupHashTable(Hashtable);
    free(outputFileName);
    return 0;
}