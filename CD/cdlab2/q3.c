#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

int main() {
    FILE *srcFile;
    char fileName[100];
    printf("Enter the name of file to open : \n");
    scanf("%s", fileName);
    srcFile = fopen(fileName, "r");
    if (srcFile == NULL) {
        printf("File cannot be opened\n");
        exit(1);
    }
    
    char *buffer = (char *)calloc(100, sizeof(char));
    int i = 0;
    char c = fgetc(srcFile);
    
    while (c != EOF) {
        if (c != '\n' && c != ' ') {  // Use single quotes for character literals
            buffer[i++] = c;
        } else {
            if (i > 0) {  // Only process if there's something in the buffer
                buffer[i] = '\0';  // Null-terminate the buffer
                bool isKeyword = checkKeyword(buffer);
                if (isKeyword) {
                    for (int j = 0; buffer[j] != '\0'; j++) {
                        putchar(toupper(buffer[j]));  // Use putchar to print characters
                    }
                }
                i = 0;  // Reset buffer index
            }
        }
        c = fgetc(srcFile);
    }
    
    free(buffer);  // Free the allocated memory
    fclose(srcFile);  // Close the file
    return 0;
}
