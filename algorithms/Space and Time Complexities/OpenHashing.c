#include<stdio.h>
#include<stdlib.h>

typedef struct linknode* link;
struct linknode{
    int value;
    link next;
};
typedef struct linknode ln;

void insert(ln** array , int element , int load){
    int index = element % load;
    ln* temp = array[index];
    while(temp->next != NULL){
        temp = temp->next;
    }
    ln* newvalue = (ln*) calloc(1,sizeof(ln));
    newvalue->value = element;
    newvalue->next = NULL;
    temp->next = newvalue;
}
void search(ln** array,int element,int load){
    int index = element % load;
    int flag = 0;
    ln* temp = array[index];
    while(temp->next != NULL){
        if(temp->value == element) flag = 1;
        temp = temp->next;
    }
    if(temp->value == element) flag = 1;
    if(flag == 1)printf("Element found\n");
    else{
        printf("Element not found\n");
    }
}
void main(){
    int length;
    printf("Enter load factor : ");
    scanf("%d",&length);
    ln** array = (ln**)calloc(length,sizeof(ln));
    for(int i = 0 ; i < length ; i++){
        array[i] = (ln*)calloc(length,sizeof(ln*));
        array[i]->next= NULL;
    }
    int length2,element;
    printf("Enter number of elements :");
    scanf("%d",&length2);
    for(int i = 0 ; i < length2 ; i++){
        printf("Enter : ");
        scanf("%d",&element);
        insert(array,element,length);
    }
    while(1){
        printf("Enter element to search: ");
        scanf("%d",&element);
        search(array,element,length);
    }
    
}