/*
Traverse any directed graph using BFS starting from one vertex
resolving ties by vertex increasing order
(i) Display visiting order
(ii) Count the number of cycles
(iii) Display type of each cycle (increasing,decreasing,mixed) along with involved vertices
*/
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

static int cycles = 0;
static int direction = 0;
void DFS(int** graph , int* visited , int n , int index){
  for(int i = 0 ; i < n ; i++){
    if(graph[index][i] == 1 && visited[i] == 1){
      cycles++;
      printf("Cycle involving vertices %d and %d: ", i, index);
            if(direction == 0){
                printf("Increasing cycle\n");
            }
            else if(direction == 1){
                printf("Decreasing cycle\n");
            }
            else if(direction == 2){
                printf("Mixed cycle\n");
            }
    }
    if(graph[index][i] == 1 && visited[i]==0){
        if(i<index)direction = 1;
        if(direction == 1 && i>index) direction = 2;
      visited[i] = 1;
      DFS(graph,visited,n,i);
    }
  }
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
    printf("\n");
    BFS(&q,graph,visited,n);
    printf("\n");
    //Now to find number of cycles 
    //we use DFS
    for(int i = 0 ; i < n ; i++){
        visited[i] = 0;
    }
    visited[0] = 1;
    DFS(graph,visited,n,0);
    printf("Number of cycles : %d",cycles);
    return 0;
}