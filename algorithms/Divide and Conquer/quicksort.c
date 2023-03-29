#include <stdio.h>
#include <stdlib.h>

void printer(int* array , int length){
    printf("\n");
    for(int i = 0 ; i < length ; i ++){
        printf("%d\t",array[i]);
    }
    printf("\n");
}

//quicksort
void swap (int *a , int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* array,int l,int r){
    int pivot = array[l];
    int i = l;
    int j = r;
    do{
        do{
            i +=1;
        } while (array[i]< pivot);
        do{
            j -= 1;
        }while(array[j] > pivot);
        swap(&array[i],&array[j]);
    }while(i < j);
    swap(&array[i],&array[j]);
    swap(&array[j],&array[l]);
    return j;
}

void Quicksort(int* array , int l , int r){
    if(l<r){
        int s = partition(array,l,r);
        Quicksort(array,l,s-1);
        Quicksort(array,s+1,r);
    }
}

void main(){
    int number;
    int length;
    printf("Enter length :");
    scanf("%d",&length);
    int* array = (int*) calloc(length,sizeof(int));
    printf("Enter array : ");
    for(int i = 0 ; i < length ; i++){
        scanf("%d",&array[i]);
    }
    printer(array,length);
    Quicksort(array,0,length);
    printer(array,length);
}