#include<stdio.h>
#include<stdlib.h>

#define NUM_SEGMENTS 5

typedef struct Segment
{
    int base;
    int limit;
}Segment;

Segment SegmentTable[NUM_SEGMENTS];

void initSegmentTable()
{
    SegmentTable[0].base = 1400;
    SegmentTable[0].limit = 1000;

    SegmentTable[1].base = 6300;
    SegmentTable[1].limit = 400;

    SegmentTable[2].base = 4300;
    SegmentTable[2].limit = 400;

    SegmentTable[3].base = 3200;
    SegmentTable[3].limit = 1100;

    SegmentTable[4].base = 4700;
    SegmentTable[4].limit = 1000;

}

int LogicaltoPhysicalAddress(int segment_no,int offset)
{
    if(segment_no < 0 || segment_no >= NUM_SEGMENTS)
    {
        printf("Segment no. is out of range.");
        return -1;
    }
    if(offset < 0 || offset >= SegmentTable[segment_no].limit)
    {
        printf("Offset is out of range for segment %d.",segment_no);
        return -1;
    }
    int physicalAddress = SegmentTable[segment_no].base + offset;
    return physicalAddress;
}

int main()
{
    initSegmentTable();
    //(i)53 byte of segment 2
    int address1 = LogicaltoPhysicalAddress(2,53);
    if(address1 != -1)
    {
        printf("Physical Address for 53 byte of segment 2:%d\n",address1);
    }

    //(ii)852 byte of segment 3
    int address2 = LogicaltoPhysicalAddress(3,852);
    if(address2 != -1)
    {
        printf("Physical Address of 852 byte of segment 3:%d\n",address2);
    }


    //(iii)1222 byte of segment 0
    int address3 = LogicaltoPhysicalAddress(0,1222);
    if(address3 != -1)
    {
        printf("Physical Address of 1222 byte of segment 0:%d\n",address3);
    }
    return 0;
}