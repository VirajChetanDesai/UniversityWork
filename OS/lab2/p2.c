#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

void printdir(char* dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "Cannot open directory\n");
        return;
    }

    chdir(dir);

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;
            printf("%*s", depth, "");
            print_permissions(statbuf.st_mode);
            printf(" %s/\n", entry->d_name);
            printdir(entry->d_name, depth + 4);
        } else {
            printf("%*s", depth, "");
            print_permissions(statbuf.st_mode);
            printf(" %s\n", entry->d_name);
        }
    }

    chdir("..");
    closedir(dp);
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(1);
    }
    char* dir = argv[1];
    printdir(dir, 0);
    return 0;
}
