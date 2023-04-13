#include<stdio.h>
#include<stdlib.h>
void insert(int* hashtable,int element,int length){
    int index = element % length;
    int startIndex = index;
    while(1){
        if(hashtable[index] == INT_MIN){
            hashtable[index] = element;
            return;
        }else{
            index = (index + 1)%length;
            if(startIndex == index) break;
        }
    }
    printf("Table full\n");
    return;
}

void search(int *hashtable,int element,int length){
    int index = element%length;
    int startIndex = index;
    while(1){
        if(hashtable[index]==element){
            printf("Element exists");
            return;
        }else{
            index = (index + 1)%length;
            if(startIndex == index) break;
        }
    }
    printf("Enter element not found");
    return;
}

void main(){
    int length;
    printf("Enter number of elements : ");
    scanf("%d",&length);
    int *array = (int*)calloc(length,sizeof(int));
    printf("Enter elements : \n");
    for (int i = 0; i < length; i++){
        scanf("%d",&array[i]);
    }
    int* hashtable = (int*)calloc(length,sizeof(int));
    for(int i = 0; i<length ; i++){
        hashtable[i] = INT_MIN;
    }
    for(int i = 0 ; i < length ; i++){
        insert(hashtable,array[i],length);
    }
    int element;
    printf("Enter element to search : ");
    scanf("%d",&element);
    search(hashtable,element,length);
}