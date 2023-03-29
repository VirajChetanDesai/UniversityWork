#include<stdio.h>
#include<stdlib.h>

void printer(int* array , int length){
    printf("\n");
    for(int i = 0 ; i < length ; i ++){
        printf("%d\t",array[i]);
    }
    printf("\n");
}

int* merge(int* array1, int* array2, int p , int q , int* array3){
    int i = 0, j = 0 , k = 0;
    while(i<p && j < q){
        if(array1[i] < array2[j]){
            array3[k] = array1[i++];
        }else{
            array3[k] = array2[j++]; 
        }
        k++;
    }
    if(i<p){
        while(i<p){
            array3[k++] = array1[i++];
        }
    }else{
        while(j<q){
            array3[k++] = array2[j++];
        }
    }
}

int* mergeSort(int* array,int length){
    if(length>1){
        int i = 0, k = 0;
        int p = 0, q = 0;
        int* A = (int*)calloc((length/2)+1,sizeof(int*));
        int* B = (int*)calloc((length/2)+1,sizeof(int*));
        for(i = 0 ; i < length/2 ; i++){
            A[k++] = array[i];
            p++;
        }
        k = 0;
        for(i = length/2; i<length;i++){
            B[k++] = array[i];
            q++;
        }
        printer(A,p);
        printer(B,q);
        mergeSort(A,p);
        mergeSort(B,q);
        merge(A,B,p,q,array);
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
    mergeSort(array,length);
    printer(array,length);
}