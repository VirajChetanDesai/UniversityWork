#include<stdio.h>
#include<stdlib.h>

void Warshalls(int** graph , int n){
    for(int k = 0 ; k < n ; k++){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(graph[i][k] * graph[k][j] == 1){
                    graph[i][j] = 1;
                }else{
                    graph[i][j] = graph[i][j];
                }
            }
        }
    }
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
}

void main(){
    int length;
    printf("Enter length:");
    scanf("%d",&length);
    int** graph = (int**) calloc(length,sizeof(int*));
    for(int i =0 ; i < length ; i++){
        graph[i] = (int*) calloc(length,sizeof(int));
    }
    printf("Enter elements: ");
    for(int i = 0 ; i < length ; i++){
        for(int j = 0 ; j<length ; j++){
            scanf("%d",&graph[i][j]);
        }
    }
    Warshalls(graph,length);
}