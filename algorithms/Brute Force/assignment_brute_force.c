#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//assignment problem
bool nextPerm(int array[], size_t length) {
    int i = length - 1; // i is length
    while (i > 0 && array[i - 1] >= array[i]){
        i--; // decrementing i until the previous element is less than current element
    }
    // 0,1,2,3 -> 3,2,1,0
    if (i == 0) return false; // everything in decreasing order
    int j = length - 1; 
    while (array[j] <= array[i - 1])
        j--; 
    // switch those two elements
    int temp = array[i - 1];
    array[i - 1] = array[j];
    array[j] = temp;
    // reverse rest of the array 
    j = length - 1;
    while (i < j) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    //0,1,3,2
    return true;
}
void printer(int* array,int n){
	for(int i = 0 ; i<n ; i++){
		printf("%d\t",array[i]);
	}
	printf("\n");
}

void main(){
	int totalworkers, totalassign;
	printf("Enter total number of workers :");
	scanf("%d",&totalworkers);
	totalassign = totalworkers;
	int **array = (int**) calloc(totalworkers,sizeof(int*));
	for(int i = 0 ; i<totalworkers ; i++){
		int* miniarray = (int*) calloc(totalassign,sizeof(int*));
		for(int j = 0 ; j<totalassign ; j++){
			printf("Enter (%d,%d) :",i,j);
			scanf("%d",&miniarray[j]);
		}
		array[i] = miniarray;
	}
	int *indices = (int*)calloc(totalworkers,sizeof(int*));
	for(int i = 0;i<totalworkers;i++){
		indices[i] = i;
	}
	int minwork = 0;
	for(int i = 0 ; i<totalworkers ; i++){
		minwork += array[i][indices[i]];
	}
	while(nextPerm(indices,totalassign)){
		printer(indices,totalworkers);
		int temp = 0;
		for(int i = 0 ; i<totalworkers ;i++){
			temp+= array[i][indices[i]];
		}
		if(temp<minwork)minwork = temp;
	}
	printf("\nmin cost: %d",minwork);
}
