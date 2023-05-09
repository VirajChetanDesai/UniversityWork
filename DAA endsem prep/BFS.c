#include<stdio.h>
#include<stdlib.h>

struct queue{
    int array[100];
    int start;
    int end;
};

void enqueue(struct queue *q, int n){
    if(q->end != 99){
        q->array[q->end++] = n;
    }
}

int dequeue(struct queue *q){
    if(q->start != q->end){
        return q->array[q->start++];
    }
    return -1;
}

void BFS(struct queue *q,int** graph,int* visited,int n){
    int element = dequeue(q);
    printf("%d\t",element);
    visited[element] = 1;
    for(int i = 0 ; i < n ; i++){
        if(graph[element][i] == 1 && visited[i] == 0){
            visited[i];
            enqueue(q,i);
        }
    }
    if(q->start == q->end) return;
    BFS(q,graph,visited,n);
}

int main(){
    int n;
    struct queue q;
    q.start = 0;
    q.end = 0;
    printf("Enter length : ");
    scanf("%d",&n);
    int** graph = (int**) calloc(n,sizeof(int*));
    for(int i = 0 ; i< n ; i ++){
        graph[i] = (int*)calloc(n,sizeof(int));
    }

    printf("Enter graph connections: ");
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(i==j) continue;
            int choice;
            printf("Are %d and %d connected :",i,j);
            scanf("%d",&choice);
            if(choice == 0) graph[i][j] = 0;
            else graph[i][j] = 1;
        }
    }
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            printf("%d\t",graph[i][j]);
        }
        printf("\n");
    }
    int* visited = (int*) calloc(n,sizeof(int*));
    for(int i = 0 ; i < n ; i++){
        visited[i] = 0;
    }
    visited[0] = 1;
    enqueue(&q,0);
    BFS(&q,graph,visited,n);
    return 0;
}