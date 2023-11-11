#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

void print_permissions(mode_t mode) {
    // Your print_permissions function implementation here
}

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void print_subdirectories_sorted(char* dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "Cannot open directory\n");
        return;
    }

    chdir(dir);

    char *subdirs[1024]; // Assuming there won't be more than 1024 subdirectories
    int subdir_count = 0;

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;

            subdirs[subdir_count++] = strdup(entry->d_name);
        }
    }

    qsort(subdirs, subdir_count, sizeof(char *), compare_strings);

    for (int i = 0; i < subdir_count; i++) {
        printf("%*s", depth, "");
        printf("%s/\n", subdirs[i]);
        print_subdirectories_sorted(subdirs[i], depth + 4);
        free(subdirs[i]);
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
    print_subdirectories_sorted(dir, 0);
    return 0;
}