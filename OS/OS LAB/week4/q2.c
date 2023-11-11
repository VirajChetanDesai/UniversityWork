#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
		struct stat sb;
	int ret;
	if (argc < 2) {
		printf ("usage: %s <file>\n", argv[0]);
		return 1;
	}
	ret = stat (argv[1], &sb);
	if (ret) {
		perror ("stat");
		return 1;
	}
	printf("The complete structure of the file is:\n");
	printf("Device ID: %ld\n",sb.st_dev);
	printf("Inode number: %ld\n",sb.st_ino);
	printf("Permissions: %d\n",sb.st_mode);
	printf("Number of hard links: %ld\n",sb.st_nlink);
	printf("User ID of owner: %d\n",sb.st_uid);
	printf("Group ID of owner: %d\n",sb.st_gid);
	printf("Device ID if special file: %ld\n",sb.st_rdev);
	printf("Total size in bytes: %ld\n",sb.st_size);
	printf("Blocksize for file system I/O: %ld\n",sb.st_blksize);
	printf("Number of blocks allocated: %ld\n",sb.st_blocks);
	printf("Last access time: %ld\n",sb.st_atime);
	printf("Last modification time: %ld\n",sb.st_mtime);
	printf("Last status change time: %ld\n",sb.st_ctime);

	return 0;
}