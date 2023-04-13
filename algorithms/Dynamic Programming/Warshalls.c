#include<stdio.h>
#include <stdlib.h>
void printer(int* array,int length){
	for(int i = 0 ; i < length ; i++){
		printf("%d\t",array[i]);
	}
	printf("\n");
}
//Warshall Algo
int opcount = 0;
void Warshalls(int** adjmatrix,int length){
	for(int k = 0 ; k<length ; k++){
		for(int i = 0 ; i < length ; i++){
			for(int j = 0 ; j < length ; j++){
				opcount++;
				if(adjmatrix[i][k]*adjmatrix[k][j] == 1)
					adjmatrix[i][j] = 1;
				else
					adjmatrix[i][j] = adjmatrix[i][j];
			}
		}
	}
	printf("\n");
	for(int i = 0 ; i < length ; i++){
		printer(adjmatrix[i],length);
	}
}

void main(){
	int length;
	printf("Enter size of the matrix : ");
	scanf("%d",&length);
	int *edges = (int*)calloc(length,sizeof(int));
	int **adjmatrix = (int**)calloc(length,sizeof(int));
	printf("Enter edges:\n");
	for(int i = 0 ; i < length ; i++){
		scanf("%d",&edges[i]);
	}
	printf("Enter connections :\n");
	for(int i = 0 ; i < length ; i++){
		int *temparray = (int*)calloc(length,sizeof(int));
		for(int j = 0 ; j < length ; j++){
			if(i==j){
				temparray[j] = 0;
				continue;
			}
			int choice;
			printf("Are %d and %d connected : (1=yes),(0=no) :",edges[i],edges[j]);
			scanf("%d",&choice);
			if(choice == 1){
				temparray[j] = 1;
			}else{
				temparray[j] = 0;
			}
		}
		adjmatrix[i] = temparray;
	}
	for(int i = 0 ; i < length ; i++){
		printer(adjmatrix[i],length);
	}
	Warshalls(adjmatrix,length);
	printf("%d",opcount);
}