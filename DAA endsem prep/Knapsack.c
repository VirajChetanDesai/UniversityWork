//knapsack implementation to solve partition problem
#include<stdio.h>
#include<stdlib.h>

int maximum(int a , int b){
	return (a>b)? a : b;
}

void knapsack(int length, int* item, int* weight, int* value, int capacity){
    int** knapsack = (int**) calloc(length+1, sizeof(int*));
    for(int i = 0 ; i < length+1 ; i++){
        knapsack[i] = (int*) calloc(capacity+1, sizeof(int));
    }
    //algorithm starts
    for(int i = 1 ; i < length+1 ; i++){
        for(int j = 1 ; j < capacity+1 ; j++){
            if(j - weight[i-1] >= 0){
                knapsack[i][j] = maximum(knapsack[i-1][j], value[i-1]+knapsack[i-1][j-weight[i-1]]);
            }else{
                knapsack[i][j] = knapsack[i-1][j];
            }
        }
    }

    //printing the knapsack
    for(int i = 0 ; i < length+1 ; i++){
        for(int j = 0 ; j < capacity+1 ; j++){
            printf("%d\t", knapsack[i][j]);
        }
        printf("\n");
    }

    //now need to backtrack to find the optimum subset
    int *subset = (int*) calloc(length, sizeof(int));
    int number = 0;
    int column = capacity;
    int row = length;
    while(row > 0 && column > 0){
        if(knapsack[row][column] == knapsack[row-1][column]){
            row--;
        }else{
            subset[number++] = item[row-1];
            column -= weight[row-1];
            row--;
        }
    }
    printf("Subset: ");
    for(int i = number-1 ; i >= 0 ; i-- ){
        printf("%d ",subset[i]);
    }
    printf("\n");
    free(subset);
    for(int i = 0 ; i < length+1 ; i++){
        free(knapsack[i]);
    }
    free(knapsack);
}

int main(){
    int length, capacity;
    printf("Enter number of available items: ");
    scanf("%d",&length);
    printf("Enter the capacity of knapsack: ");
    scanf("%d",&capacity);
    int* weight = (int*)calloc(length, sizeof(int));
    int* value = (int*) calloc(length, sizeof(int));
    int* item = (int*)calloc(length, sizeof(int));
    printf("Enter item names: ");
    for(int i = 0; i < length; i++){
        scanf("%d",&item[i]);
    }
    printf("Enter weights: ");
    for(int i = 0; i < length; i++){
        scanf("%d",&weight[i]);
    }
    printf("Enter values: ");
    for(int i = 0; i < length; i++){
        scanf("%d",&value[i]);
    }
    knapsack(length, item, weight, value, capacity);
    free(item);
    free(weight);
    free(value);
    return 0;
}
