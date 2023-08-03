//To reverse the file contents and store in another file. Also display the size of file using file handling function
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *srcFile, *endFile;
    char fileName[100], fileName2[100], c;
    printf("Enter name of the file: \n");
    scanf("%s", fileName);

    srcFile = fopen(fileName, "r");
    if (srcFile == NULL) {
        printf("Cannot open file %s\n", fileName);
        exit(1);
    }
    printf("Enter name of file to put the reversed contents: \n");
    scanf("%s", fileName2);
    endFile = fopen(fileName2, "w+");
    if (endFile == NULL) {
        printf("Cannot open file %s\n", fileName2);
        fclose(srcFile);
        exit(1);
    }
    fseek(srcFile, -1, SEEK_END);
    while (ftell(srcFile) > 0) {
        c = fgetc(srcFile);
        fputc(c, endFile);
        fseek(srcFile, -2, SEEK_CUR);
    }
    // Since the loop stops at the beginning of the file, we need to write the first character separately.
    c = fgetc(srcFile);
    fputc(c, endFile);
    fclose(srcFile);
    fclose(endFile);
    return 0;
}
