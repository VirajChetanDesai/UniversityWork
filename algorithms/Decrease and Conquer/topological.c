#include<stdio.h>
#include<stdlib.h>

int isEmpty(int top){
    if(top == -1) return 1;
    else return 0;
}

int isFull(int top, int size){
    if(top == size - 1) return 1;
    else return 0;
}

void push(int* stack, int* top , int size ,int value){
    if(isFull(*top,size)){
        printf("Stack Full\n");
    }else{
        stack[++(*top)] = value;
    }
}

int pop(int* stack,int* top){
    if(isEmpty(*top)){
        printf("Empty Stack");
        return -1;
    }else{
        return stack[(*top)--];
    }
}

void addEdge(int start,int end,int** array){
    if(start!=end){
    //directed graph
        array[start][end] = 1;
    }
}

//static int maxtop = -1;
int* DFS(int index,int* visited,int** adjarray,int n,int* stack,int* top,int size){
    //if(*top >= maxtop) maxtop = *top;
    //*top = maxtop;
    int j;
    printf("%d\n",index);
    push(stack,top,size,index);
    printf("%d\n",*top);
    visited[index]=1;
    for(j=0;j<n;j++){
        if(visited[j]!=1&&adjarray[index][j]==1) DFS(j,visited,adjarray,n,stack,top,size);
    }
    return stack;
}

int* SourceRemoval(int startIndex,int* visited,int** adjarray,int n, int* indegree,int* finorder,int* vertices,int count){
    printf("%d\n",startIndex);
    visited[startIndex] = -1;
    finorder[count++] = vertices[startIndex];
    int min = n;
    for(int j = 0; j < n ; j++){
        if(adjarray[startIndex][j] == 1){
            if(j<min && visited[j]!=-1) min = j;
            if(indegree[j]>0) indegree[j] = --indegree[j];
        }
    }
    if (count == n-1 || min == n) return finorder;
    return SourceRemoval(min,visited,adjarray,n,indegree,finorder,vertices,count);
}

    int main() {
    int* top = (int*) malloc(sizeof(int));
    *top = -1;
    int size = 100;
    int n;
    int* stack = (int*) calloc(size,sizeof(int));
    printf("Enter number of nodes : ");
    scanf("%d", &n);
    int* visited = (int*) calloc(n,sizeof(int));
    int* vertices = (int*) calloc(n,sizeof(int));
    int** adjarray = (int**) calloc(n,sizeof(int*));
    for(int i = 0 ; i < n ; i++){
        printf("Enter value of vertice : ");
        scanf("%d", &vertices[i]);
    }
    for(int i = 0 ; i < n ; i++){
        int *temparray = (int*) calloc(n,sizeof(int));
        for(int j = 0 ; j < n ; j++){
            temparray[j] = 0;
        }
        adjarray[i] = temparray;
    }
    printf("Enter edges :");
    int check = 1;
    while(check){
        int startvert,endvert;
        printf("Enter edge : ");
        scanf("%d %d", &startvert, &endvert);
        int start=-1,end=-1;
        for(int i = 0 ; i < n ; i++){
            if(vertices[i] == startvert){
                start = i;
            }
        }
        if(start == -1) {
            printf("Invalid/Not found");
            continue;
        }
        for(int i = 0; i<n ; i++){
            if(vertices[i] == endvert){
                end = i;
            }
        }
        if(end == -1){
            printf("Invalid/Not found");
            continue;
        }
        addEdge(start,end,adjarray);
        printf("Edge added , do you want to continue (0 to exit):");
        scanf("%d",&check);
    }
    for(int i = 0 ; i < n ; i++){
        visited[i] = 0 ;
    }
    DFS(0,visited,adjarray,n,stack,top,size);
    printf("Topological Sort using DFS\n");
    while(isEmpty(*top)==0){
        printf("%d\t",vertices[pop(stack,top)]);
    }

    //Implementing Source Removal 
    int* indegree = (int*) calloc(n,sizeof(int));
    for(int i = 0 ; i < n ; i++){
        int indeg = 0;
        for(int j = 0 ; j < n ; j++){
            if(adjarray[j][i] == 1) indeg++;
        }
        indegree[i] = indeg;
    }
    int min_indegree = n+1;
    for(int i = 0 ; i < n ; i++){
        if(indegree[i]<min_indegree){
            min_indegree = i;
        }
        visited[i] = 0;
    }
    printf("\nTopological Sort Using Source Removal Method : \n");
    int* finorder = (int*) calloc(n,sizeof(int));
    finorder = SourceRemoval(min_indegree,visited,adjarray,n,indegree,finorder,vertices,0);
    for(int i = 0 ; i < n ; i++){
        printf("%d\t",vertices[finorder[i]]);
    }
    return 0;
}
