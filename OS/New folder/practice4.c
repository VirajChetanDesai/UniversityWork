#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int page_number;
    int second_chance_bit;
} pageFrame;

void initFrames(pageFrame frames[] , int num_frames){
    for(int i = 0 ; i < num_frames ; i++){
        frames[i].page_number = -1;
        frames[i].second_chance_bit = 0;
    };
}

int isPageInFrames(pageFrame frames[] , int num_frames , int pagenumber){
    for(int i = 0 ; i < num_frames ; i++){
        if(frames[i].page_number == pagenumber){
            return 1;
        }else return 0;
    }
}

int pageReplacement(pageFrame frames[] , int num_frames , int pagenumber){
    while(1){
        for(int i = 0 ; i < num_frames ; i++){
            if(frames[i].second_chance_bit == 1){
                frames[i].second_chance_bit = 0;
            }else{
                return i;
            }
        }
    }
}

void main(){
    pageFrame frames[100];
    int num_frames = 4;
    int page_faults = 0;
    int page_hits = 0;
    int current_frame_index = 0;
    int page_references_length = 8;
    int page_references[] = {1,2,4,2,3,5,6,4};
    initFrames(frames,frames);
    for(int i = 0 ; i < page_references_length ; i++){
        int page_number = page_references[i];
        printf("%d",page_number);
        if(isPageInFrames(frames,num_frames,page_number)){
            page_hits++;
            frames[i].second_chance_bit  = 1;
        }else{
            page_faults++;
            int replaceIndex = pageReplacement(frames,num_frames,page_number);
            frames[i].page_number = page_number;
            frames[i].second_chance_bit = 0;
        }
    }
    printf("%d / %d",page_faults,page_hits);
}
