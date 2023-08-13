#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h> // Include time.h for handling time-related functions

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-"); // read
    printf((mode & S_IWUSR) ? "w" : "-"); // write
    printf((mode & S_IXUSR) ? "x" : "-"); // execute
    printf((mode & S_IRGRP) ? "r" : "-"); // read grp
    printf((mode & S_IWGRP) ? "w" : "-"); // write grp
    printf((mode & S_IXGRP) ? "x" : "-"); // execute grp
    printf((mode & S_IROTH) ? "r" : "-"); // read others
    printf((mode & S_IWOTH) ? "w" : "-"); // write others
    printf((mode & S_IXOTH) ? "x" : "-"); // execute others
}

void printdir(char* dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    struct tm *timeinfo; // Structure to hold time information

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
            printf(" %ld", (long)statbuf.st_nlink);
            timeinfo = localtime(&statbuf.st_atime);
            printf(" %s", asctime(timeinfo));
            printf(" %s/\n", entry->d_name);
            printdir(entry->d_name, depth + 4);
        } else {
            printf("%*s", depth, "");
            print_permissions(statbuf.st_mode);
            printf(" %ld", (long)statbuf.st_nlink);
            timeinfo = localtime(&statbuf.st_mtime);
            printf(" %s", asctime(timeinfo));
            printf(" %s\n", entry->d_name);
        }
    }

    chdir("..");
    closedir(dp);
}

int main() {
    printdir(getenv("PWD"), 0);
    return 0;
}
