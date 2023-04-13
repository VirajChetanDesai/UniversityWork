#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Horspools algorithm for string matching
void printer(int* arr,int length){
	for(int i = 0 ; i < length ; i ++){
		printf("%d\t",arr[i]);
	}
}

void createShiftTable(char* pattern, int* shiftTable , int patternLength) {
    int alphaLength = 26;
    for(int i = 0; i < alphaLength; i++) {
        shiftTable[i] = patternLength;
    }
    for(int j = 0; j < patternLength - 1; j++) { 
        int alphabet = pattern[j];
        shiftTable[alphabet - 97] = patternLength - j - 1; 
    }
}

int HorspoolMatching(char* pattern , char* text) {
    int patternLength = strlen(pattern);
    int textLength = strlen(text);
    int* shiftTable = (int*) calloc(26, sizeof(int));
    createShiftTable(pattern, shiftTable, patternLength);
    printer(shiftTable,26);
    int i = patternLength - 1;
    while(i < textLength) {
        int k = 0;
        while(k < patternLength && pattern[patternLength - 1 - k] == text[i - k]) {
            k++;
        }
        if(k == patternLength) {
            return i - patternLength + 1;
        }
        else {
        	if(text[i-k] == '_' || text[i-k] == ' ') i+=patternLength;
        	else{
        		i += shiftTable[text[i] - 97]; 
        	}   
        }
    }
    return -1;
}

int main() { // changed return type to int
    char* pattern = (char*) calloc(100, sizeof(char));
    char* text = (char*) calloc(100, sizeof(char));
    printf("Enter Text : \n");
    scanf("%s", text);
    printf("Enter Pattern :");
    scanf("%s", pattern);
    int index = HorspoolMatching(pattern, text);
    if (index != -1) {
        printf("Pattern found at index %d\n", index);
    }
    else {
        printf("Pattern not found\n");
    }
    return 0;
}
