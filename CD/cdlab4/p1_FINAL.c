#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexical.h"

void processToken(const char* tokenName, enum TokenType tokenType, unsigned int row, unsigned int col, HashTable* Hashtable) {
    const char* typeString = NULL;
    HashEntry* entry = lookup(Hashtable, tokenName);
    if (entry != NULL) {
        printToken(entry->type, entry->name, entry->index, row, col);
        return;
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
        case FUNCTION:
            typeString = "function";
            break;
    }

    if (typeString != NULL) {
        printToken(typeString, tokenName, 0, row, col);
        insert(Hashtable, tokenName, Hashtable->index++, typeString, "", "", "", "");
    }
    
    // Special handling for SPECIAL_SYMBOL token type
    if (tokenType == SPECIAL_SYMBOL) {
        printToken("special_symbol", tokenName, Hashtable->index++, row, col); // Adjust the type name as needed
        insert(Hashtable, tokenName, Hashtable->index - 1, "special_symbol", "", "", "", "");
    }
}
bool isSpecialSymbol(char c) {
    // Define a list of special symbols you want to detect.
    // For example, you can include parentheses, curly braces, and square brackets.
    const char specialSymbols[] = "(){}[]";
    for (int i = 0; specialSymbols[i] != '\0'; i++) {
        if (c == specialSymbols[i]) {
            return true;
        }
    }
    return false;
}

void lexicalAnalyser(const char* outputFileName, HashTable* Hashtable) {
    char c;
    char buf[5000];
    char previous[5000];
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
            if (isSpecialSymbol(c)) {
                buf[i++] = c;
                buf[i] = '\0';
                // Process the special symbol as a token
                processToken(buf, SPECIAL_SYMBOL, row, col, Hashtable);
                continue; // Skip the rest of the loop iteration
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
            } else {
                HashEntry* entry = lookup(Hashtable, buf);
                if (entry != NULL) {
                    printToken("id", entry->name, entry->index, row, col);
                } else {
                    if(c == '(' && checkKeyword(previous)){
                        insert(Hashtable, buf , Hashtable->index++, "function", "", "", "", previous);
                        printf("<%s,%d,%u,%u,%s>\n", "function", Hashtable->index - 1, row, col, previous);
                    }
                    processToken(buf, IDENTIFIER, row, col, Hashtable);
                }
            }
            int j = 0;
            while (buf[j] != '\0') {
                previous[j] = buf[j];
                j++;
            }
            previous[j] = '\0'; // Ensure null termination
            
            fseek(fp, -1, SEEK_CUR);
        }
    }
    fclose(fp);
}


void printHashTable(const HashTable* ht) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashEntry* entry = ht->table[i];
        while (entry != NULL) {
            printf("Index %d:\n", i);
            printf("  Name: %s\n", entry->name);
            printf("  Index: %d\n", entry->index);
            printf("  Type: %s\n", entry->type);
            entry = entry->next;
        }
    }
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
    printHashTable(Hashtable); // Print the hash table
    cleanupHashTable(Hashtable);
    free(outputFileName);
    return 0;
}
