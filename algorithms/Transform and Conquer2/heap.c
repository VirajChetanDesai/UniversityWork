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
        printf("%d", heap[i]);
    }
    return 0;
}
 /*
 OUTPUT
 Enter the number of elements: 5
Enter element: 1
Enter element: 2
Enter element: 3
Enter element: 4
Enter element: 5
Heap:
54213
 */