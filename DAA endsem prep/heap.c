#include<stdio.h>
#include<stdlib.h>

int swap(int *a  , int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int *heap,int element , int size){
    int i = size+1;
    heap[i] = element;
    while (i>1  && heap[i]>heap[i/2])   {
        swap(&heap[i], &heap[i/2]);
        i = i/2;
    }
}

void build_heap(int* heap , int* array ,int size){
    for(int i = 0 ; i < size ; i++){
        insert(heap,array[i],i);
    }
}

void heapify(int* heap , int size){
    for(int i = size ; i>1 ;i--){
        int j = i;
        while(j>1 && heap[j]>heap[j/2]){
            swap(&heap[j],&heap[j/2]);
            j = j/2;
        }
    }
}

int checker(int* heap, int size){
    for(int i = size ; i>=1 ; i--){
        int j = i;
        while(j>1 && heap[j]>heap[j/2]){
            return 0;
        }
    }
    return 1;
}

int delete(int* heap, int size , int element){
    int index = -1;
    for(int i = 1 ; i <= size ; i++){
        if(heap[i] == element) index = i;
    }
    if(index == -1) {
        printf("Element not found");
        return size;
    }
    swap(&heap[index],&heap[size]);
    heap[size] = 0;
    heapify(heap,size);
    size = size -1;
    return size;
}

int main(){
    int size;
    printf("Enter the size of the heap: ");
    scanf("%d",&size);
    int * heap = (int*) calloc(size , sizeof(int));
    int * array = (int*) calloc(size,sizeof(int));
    for(int i = 0 ; i < size ; i++){
        scanf("%d",&array[i]);
    }
    build_heap(heap,array,size);
    printf("Heap :\n");
    for(int i = 1 ; i <= size ; i++){
        printf("%d\t",heap[i]);
    }
    printf("\nDeleting element\n");
    size = delete(heap,size,1);
    printf("\n");
    for(int i = 1 ; i <= size ; i++){
        printf("%d\t",heap[i]);
    }
    printf("\n");
    //maxheap
    int* finalarray = (int*) calloc(size,sizeof(int));
    int k = 0;
    while(heap[1]!=0){
        finalarray[k++] = heap[1];
        heap[1] = heap[size-k];
        heap[size-k] = 0;
        heapify(heap,size);
    }
    printf("\nOrdered deletion form max-heap : \n");
    for(int i = 0 ; i < size ; i++){
        printf("%d\t",finalarray[i]);
    }
    int isHeap = checker(heap,size);
    if(isHeap == 1) printf("Heap\n");
    else printf("Not heap\n");
    int* array2 =  (int*)calloc(10,sizeof(int*)) ;
    for(int i =  1 ; i < 11 ; i++){
        array2[i] = rand();
    }
    isHeap = checker(array2,10);
    if(isHeap == 1) printf("Heap\n");
    else printf("Not heap\n");
    return 0;
}