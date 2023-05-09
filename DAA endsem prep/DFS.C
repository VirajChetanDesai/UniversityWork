#include<stdio.h>
#include<stdlib.h>

void DFS(int** matrix, int* visited,int start,int n){
    printf("%d",start);
    for(int i = 0 ; i< n ; i++){
        if(matrix[start][i] == 1 && visited[i] == 0){
            visited[i] = 1;
            DFS(matrix,visited,i,n);
        }
    }
}

void main(){
    int m;
    printf("Enter dimension of adjacency matrix: ");
    scanf("%d",&m);
    printf("Enter vlaue in adjacency matrix: ");
    int** matrix = (int**)calloc(m,sizeof(int));
    int* visited = (int*)calloc(m,sizeof(int));
    for(int i = 0 ; i < m ; i++){
        visited[i] = 0;
    }
    for(int i = 0 ; i < m ; i++){
        int* row = (int*)calloc(m,sizeof(int));
        for(int j = 0 ; j < m ; j++){
            scanf("%d",&row[j]);
        }
        matrix[i] = row;
    }
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j < m ; j++){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }

    DFS(matrix,visited,0,m);
}