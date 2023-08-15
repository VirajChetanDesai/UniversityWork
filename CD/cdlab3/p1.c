#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

enum TokenType {
    STRING_LITERAL,
    RELATIONAL_OPERATOR,
    ASSIGNMENT_OPERATOR,
    ARITHMETIC_OPERATOR,
    LOGICAL_OPERATOR,
    INVALID_OPERATOR,
    KEYWORD,
    IDENTIFIER
};

struct Token {
    char token_name[100];
    int index;
    unsigned int row, col;
    enum TokenType type;
};

void printToken(const char* tokenType, const char* tokenName, int index, unsigned int row, unsigned int col) {
    printf("<%s,%d,%u,%u>%s\n", tokenType, 0, row, col, tokenName);
}

void processToken(const char* tokenName, enum TokenType tokenType, unsigned int row, unsigned int col) {
    const char* typeString = NULL;

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
    char c, prev = '\0';
    int flag = 0; // Tracks whether inside a directive
    int insideString = 0; // Tracks whether inside a string literal
    while ((c = fgetc(srcFile)) != EOF) {
        if (c == '"' && prev != '\\') {
            insideString = !insideString; // Toggle insideString when a non-escaped double quote is found
        }
        
        if (!insideString) {
            if (c == '#' && prev != '\\') {
                flag = 1; // Start of directive
            }
            
            if (flag == 1) {
                if (c == '\n') {
                    flag = 0; // End of directive
                }
            } else {
                fputc(c, tgtFile); // Write the character if not inside a directive
            }
        } else {
            fputc(c, tgtFile); // Write the character if inside a string
        }        
        prev = c; 
    }    
    fclose(srcFile);
    fclose(tgtFile);
}
void lexicalAnalyser(const char* outputFileName) {
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
        if (c == '"' || c == "'") {
            char opening_quote = c;
            buf[i++] = c;
            while ((c = fgetc(fp)) != EOF) {
                buf[i++] = c;
                if (c == '\\') {
                    // Handle escape sequences within string/character literals if needed
                } else if (c == opening_quote) {
                    buf[i] = '\0';
                    processToken(buf, STRING_LITERAL, row , col);
                    break;
                }
            }
        } else if (c == '=') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=') {
                buf[i++] = c;
                buf[i] = '\0';
                processToken(buf, RELATIONAL_OPERATOR, row , col);
            } else {
                buf[i] = '\0';
                processToken(buf, ASSIGNMENT_OPERATOR, row , col);
                fseek(fp, -1, SEEK_CUR);
            } 
        } else if (c == '<' || c == '>' || c == '!') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == '=') {
                buf[i++] = c;
                buf[i] = '\0';
                processToken(buf, RELATIONAL_OPERATOR, row , col);
            } else {
                buf[i] = '\0';
                processToken(buf, RELATIONAL_OPERATOR , row , col);
                fseek(fp, -1, SEEK_CUR);
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            buf[i++] = c;
            buf[i] = '\0';
            processToken(buf, ARITHMETIC_OPERATOR, row , col);
        } else if (c == '&' || c == '|') {
            buf[i++] = c;
            c = fgetc(fp);
            if (c == buf[0]) {
                buf[i++] = c;
                buf[i] = '\0';
                processToken(buf, LOGICAL_OPERATOR , row , col);
            } else {
                buf[i] = '\0';
                processToken(buf, INVALID_OPERATOR, row , col);
                fseek(fp, -1, SEEK_CUR);
            }
        } else if (isalpha(c) || c == '_') {
            while (isalnum(c) || c == '_') {
                buf[i++] = c;
                c = fgetc(fp);
            }
            buf[i] = '\0';

            if (checkKeyword(buf)) {
                processToken(buf, KEYWORD, row , col);
            } else {
                processToken(buf, IDENTIFIER, row , col);
            }
            fseek(fp, -1, SEEK_CUR);
        }
    }
    fclose(fp);
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
    removeCommentsAndDirectives(inputFileName, outputFileName);
    lexicalAnalyser(outputFileName);
    free(outputFileName);
    return 0;
}