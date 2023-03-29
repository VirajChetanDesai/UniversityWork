#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int graph[MAX][MAX];
int visited[MAX] = {0};
int vertex[MAX];

struct queue{
    int array[MAX];
    int start;
    int end;
};
typedef struct queue queue;

void enqueue(queue *q,int element){
    if(q->end != MAX){
        printf("Queue Full");
        return ;
    }else{
        q->array[q->end++] = element;
    }
}

int dequeue(queue *q){
    if(q->end == q->start){
        printf("Queue Empty");
        q->start = 0;
        q->end = 0;
        return -1;
    }else{
        int element = q->array[q->start++];
    }
}

void BFS(queue *q,int length){
        int currentVertex = dequeue(q);
        printf("%d",vertex[currentVertex]);
        for(int i = 0 ; i<length; i++){
            if(graph[currentVertex][i]==1 && visited[i] != 0){
                visited[i] = 1;
                enqueue(q,i);
            }
        }
        if(q->start == q->end) return;
        bfs(q,length);
}

void main(){
    queue *q = (queue*)calloc(1,sizeof(queue));
    q->start = 0;
    q->end = 0;
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
    enqueue(q,min_index);
    bfs(q,length);
}