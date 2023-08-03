#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file1, *file2, *file3;
    char fileName1[100], fileName2[100], fileName3[100];
    printf("Enter filename to open for reading (1):\n");
    scanf("%s", fileName1);
    file1 = fopen(fileName1, "r");
    if (file1 == NULL) {
        printf("Cannot open file %s\n", fileName1);
        exit(1);
    }
    printf("Enter filename to open for reading (2):\n");
    scanf("%s", fileName2);
    file2 = fopen(fileName2, "r");
    if (file2 == NULL) {
        printf("Cannot open file %s\n", fileName2);
        exit(1);
    }
    printf("Enter filename to open for writing (3):\n");
    scanf("%s", fileName3);
    file3 = fopen(fileName3, "w+");
    if (file3 == NULL) {
        printf("Cannot open file %s\n", fileName3);
        exit(1);
    }
    char c1, c2;
    c1 = fgetc(file1);
    c2 = fgetc(file2);
    while (c1 != EOF && c2 != EOF) {
        while (c1 != EOF && c1 != '\n') {
            fputc(c1, file3);
            c1 = fgetc(file1);
        }
        if (c1 == '\n') {
            fputc(c1, file3);
            c1 = fgetc(file1);
        }
        printf("File1 done\n");
        while (c2 != EOF && c2 != '\n') {
            fputc(c2, file3);
            c2 = fgetc(file2);
        }
        if (c2 == '\n') {
            fputc(c2, file3);
            c2 = fgetc(file2);
        }
        printf("File2 done\n");
    }
    fclose(file1);
    fclose(file2);
    fclose(file3);
    return 0;
}
