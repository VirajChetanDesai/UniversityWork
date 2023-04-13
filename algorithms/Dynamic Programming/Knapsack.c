//knapsack
#include<stdio.h>
#include<stdlib.h>

int maximum(int a , int b){
	return (a>b)? a : b;
}

void knapsack(int** array ,int* weight , int* value , int length , int capacity){
	for(int i = 1 ; i<length+1 ; i++){
		for(int j = 1; j< capacity+1 ; j++){
			if(j - weight[i-1] >= 0){
				printf("%d %d %d %d\n",i,j,weight[i-1],value[i-1]);
				array[i][j] = maximum(array[i-1][j],value[i-1] + array[i-1][j-weight[i-1]]);
			}else{
				array[i][j] = array[i-1][j];
			}
		}
	}
}

void scanner(int *array , int length){
	for(int i = 0 ; i < length ; i++){
		scanf("%d",&array[i]);
	}
}

void printer(int* array , int length){
	for(int i = 0 ; i < length ; i++){
		printf("%d\t",array[i]);
	}
	printf("\n");
}

void main(){
	int length,capacity;
	printf("Enter number of elements: ");
	scanf("%d",&length);

	int* item = (int*)calloc(length,sizeof(int));
	printf("Enter item names :");
	scanner(item,length);
	int* weight = (int*)calloc(length,sizeof(int));
	printf("Enter weights of items :");
	scanner(weight,length);
	int* value = (int*)calloc(length,sizeof(int));
	printf("Enter value of items :");
	scanner(value,length);
	

	printf("Enter capacity :");
	scanf("%d",&capacity);

	int** matrix = (int**)calloc(100,sizeof(int));
	for(int i = 0 ; i < length+1 ; i++){
		int* temparray = (int*)calloc(100,sizeof(int));
		for(int j = 0 ; j < capacity+1 ; j++){
			temparray[j] = 0;
		}
		matrix[i] = temparray;
	}
	printf("\n");
	knapsack(matrix,weight,value,length,capacity);
	for(int i = 0 ; i < length+1 ; i++){
		printer(matrix[i],capacity+1);
	}
	return;
}