#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void remove_file(const char *filename) {
    printf("Do you want to remove %s? (y/n): ", filename);
    char response[10];
    fgets(response, sizeof(response), stdin);

    if (response[0] == 'y' || response[0] == 'Y') {
        if (remove(filename) == 0) {
            printf("%s has been removed.\n", filename);
        } else {
            perror("Error removing file");
        }
    } else {
        printf("%s was not removed.\n", filename);
    }
}

int main() {
    DIR *dp;
    struct dirent *entry;

    dp = opendir(".");
    if (dp == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    printf("Files in the current directory:\n");

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
            remove_file(entry->d_name);
        }
    }

    closedir(dp);

    return 0;
}
