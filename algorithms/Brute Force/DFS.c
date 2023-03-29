#include<stdio.h>
#include<stdlib.h>
#define max_int 100

int graph[max_int][max_int];
int visited[max_int] = {0};
int vertex[max_int];

void dfs(int index , int length){
    printf("%d",vertex[index]);
    for(int i = 0 ; i < length ; i++){
        if(i!=index && visited[i]==0){
            visited[i] = 1;
            dfs(i,length);
        }
    }
}

void main(){
    int length,a,b;
    int min_index = 0;
    printf("Enter length of array : ");
    scanf("%d",&length);
    for(int i = 0 ; i < length ; i++){
        scanf("%d",&vertex[i]);
        if(vertex[i] < vertex[min_index]) min_index = i;
    }
    while(1){
            printf("Enter connected edges: (enter -1,-1 to break):");
            scanf("%d %d",&a,&b);
            if(a == -1 & b == -1) break;
            graph[a][b] = 1;
            graph[b][a] = 1;
    }  
    visited[min_index] = 1; 
    dfs(min_index,length);
}