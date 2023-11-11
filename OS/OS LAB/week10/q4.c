#include <stdio.h>
#include <stdlib.h>
#define DISK_SIZE 100
#define SPARE_BLOCKS 5

struct Disk {
    char blocks[DISK_SIZE];
    int bad_blocks_table[DISK_SIZE];
    int spare_block_index;
};

void initialize_disk(struct Disk *disk) {
    for (int i = 0; i < DISK_SIZE; ++i) {
        disk->blocks[i] = 'G';  // G for Good block
        disk->bad_blocks_table[i] = -1;  // -1 indicates no bad block
    }
    disk->spare_block_index = DISK_SIZE - SPARE_BLOCKS; // Initialize spare block index
}

// Mark a block as bad
void mark_bad_block(struct Disk *disk, int block_number) {
    if (block_number < 0 || block_number >= DISK_SIZE) {
        printf("Block number out of range\n");
        return;
    }
    disk->blocks[block_number] = 'B';  // B for Bad block
}

// Allocate a spare block for a bad block
int allocate_spare_block(struct Disk *disk, int bad_block_number) {
    if (disk->bad_blocks_table[bad_block_number] != -1) {
        // Spare block is already allocated
        return disk->bad_blocks_table[bad_block_number];
    }

    if (disk->spare_block_index < DISK_SIZE) {
        disk->blocks[disk->spare_block_index] = 'S';  // S for Spare block
        disk->bad_blocks_table[bad_block_number] = disk->spare_block_index;
        disk->spare_block_index++;
        return disk->bad_blocks_table[bad_block_number];
    } else {
        printf("No spare blocks left to allocate\n");
        return -1;
    }
}

// Read a block, considering bad blocks
int read_block(struct Disk *disk, int block_number) {
    if (block_number < 0 || block_number >= DISK_SIZE) {
        printf("Block number out of range\n");
        return -1;
    }

    if (disk->blocks[block_number] == 'B') {
        // Block is bad, use its spare block
        return disk->bad_blocks_table[block_number];
    }
    // Block is good, read directly
    return block_number;
}

int main() {
    struct Disk myDisk;
    initialize_disk(&myDisk);

    // Mark blocks as bad
    mark_bad_block(&myDisk, 10);
    mark_bad_block(&myDisk, 20);

    // Allocate spare blocks to bad blocks
    int spare_for_block_10 = allocate_spare_block(&myDisk, 10);
    int spare_for_block_20 = allocate_spare_block(&myDisk, 20);

    // Read blocks from the disk
    int read_from_block_10 = read_block(&myDisk, 10);
    int read_from_block_20 = read_block(&myDisk, 20);
    int read_from_block_30 = read_block(&myDisk, 30); // Assuming block 30 is a good block

    printf("Spare for block 10: %d\n", spare_for_block_10);
    printf("Spare for block 20: %d\n", spare_for_block_20);
    printf("Read from block 10: %d\n", read_from_block_10);
    printf("Read from block 20: %d\n", read_from_block_20);
    printf("Read from block 30: %d\n", read_from_block_30);

    return 0;
}



/*#include <stdio.h>
#include<stdlib.h>
struct disk
{
    char data;
};
typedef struct disk disk;
int main() {
    int TOTAL_BLOCKS=10;
    disk disks[TOTAL_BLOCKS];

    char c = 'a';
    for(int m=0;m<8;m++)
    {
        disks[m].data=(char)c;
        c++;
    }
    int bad_blocks_table[2][2];
    bad_blocks_table[0][0]=5;
    bad_blocks_table[0][1]=8;
    bad_blocks_table[1][0]=6;
    bad_blocks_table[1][1]=9;
    disks[8].data=disks[5].data;
    disks[9].data=disks[6].data;

    int num=0, diskNum=0;
    printf("Enter number of disks you wish to access:\n");
    scanf("%d",&num);
    for (int i = 0; i < num; i++) {
        printf("Enter disk number\n");
        scanf("%d",&diskNum);

        for(int j=0;j<2;j++)
        {
            if(bad_blocks_table[j][0]==diskNum)
                diskNum=bad_blocks_table[j][1];
        }
        printf("\nThe data on the disk is: %c\n",disks[diskNum].data);
    }
    return 0;
}*/