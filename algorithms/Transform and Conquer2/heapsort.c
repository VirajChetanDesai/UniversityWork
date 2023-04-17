#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int* heap, int element, int size){
    int i = size + 1;
    heap[i] = element;
    while (i > 1 && heap[i] > heap[i/2]) {
        swap(&heap[i], &heap[i/2]);
        i = i/2;
    }
}

void build_heap(int* heap,int* array, int size){
    for(int i = 0 ; i < size ; i++){
        insert(heap, array[i] , i);
    }
}

void heapify(int *heap,int size){
    for(int i = size; i>1 ; i--){
        int j = i;
        while (j > 1 && heap[j/2] < heap[j]) {
            swap(&heap[j], &heap[j/2]);
            j = j/2;
        }
    }
}

int main(){
    int size;
    printf("Enter the number of elements: ");
    scanf("%d",&size);
    int* heap = (int*) calloc(size+1, sizeof(int));
    int* array = (int*) calloc(size,sizeof(int));
    for(int i = 0 ; i < size ; i++){
        printf("Enter element: ");
        scanf("%d",&array[i]);
    }
    build_heap(heap, array, size);
    printf("Heap:\n");
    for(int i = 1 ; i <= size ; i++){
        printf("%d\t", heap[i]);
    }
    int* finarray = (int*) calloc(size,sizeof(int));
    int k = 0;
    while(heap[1]!=0){
        finarray[k++] = heap[1];
        heap[1]=heap[size-k];
        heap[size-k] = 0;
        heapify(heap,size);
    }
    printf("\nFinal Array :");
    for(int i = 0 ; i <size ; i++){
        printf("%d\t",finarray[i]);
    }
    return 0;
}
/*
OUTPUT
Enter the number of elements: 10
Enter element: 10
Enter element: 9
Enter element: 8
Enter element: 7
Enter element: 1
Enter element: 2
Enter element: 3
Enter element: 4
Enter element: 5
Enter element: 6
Heap:
10      9       8       7       6       2       3       4       5       1
Final Array :10 9       8       7       6       5       4       3       2       1*/