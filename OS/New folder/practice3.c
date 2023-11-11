#include <stdio.h>
#define NUM_SEGMENTS 5
#define SEGMENT_SIZE 256
struct SegmentTableEntry {
    int base;  // Base address of the segment
    int limit; // Limit of the segment
};
void initializeSegmentTable(struct SegmentTableEntry segmentTable[]) {
    segmentTable[0].base = 0;
    segmentTable[0].limit = 256;

    segmentTable[1].base = 256;
    segmentTable[1].limit = 256;

    segmentTable[2].base = 512;
    segmentTable[2].limit = 256;

    segmentTable[3].base = 768;
    segmentTable[3].limit = 256;

    segmentTable[4].base = 1024;
    segmentTable[4].limit = 256;
}

// Function to convert a logical address to a physical address
int logicalToPhysical(struct SegmentTableEntry segmentTable[], int segmentNumber, int offset) {
    // Check if the segment number is valid
    if (segmentNumber < 0 || segmentNumber >= NUM_SEGMENTS) {
        printf("Invalid segment number\n");
        return -1; // Return an error code
    }

    // Check if the offset is within the segment's limit
    if (offset < 0 || offset >= segmentTable[segmentNumber].limit) {
        printf("Invalid offset within the segment\n");
        return -1; // Return an error code
    }

    // Calculate the physical address
    int physicalAddress = segmentTable[segmentNumber].base + offset;
    return physicalAddress;
}

int main() {
    struct SegmentTableEntry segmentTable[NUM_SEGMENTS];
    initializeSegmentTable(segmentTable);

    // Compute the physical addresses
    int logicalAddress1 = logicalToPhysical(segmentTable, 2, 53);
    int logicalAddress2 = logicalToPhysical(segmentTable, 3, 852);
    int logicalAddress3 = logicalToPhysical(segmentTable, 0, 1222);

    printf("(i) 53 byte of segment 2: Physical Address = %d\n", logicalAddress1);
    printf("(ii) 852 byte of segment 3: Physical Address = %d\n", logicalAddress2);
    printf("(iii) 1222 byte of segment 0: Physical Address = %d\n", logicalAddress3);

    return 0;
}
