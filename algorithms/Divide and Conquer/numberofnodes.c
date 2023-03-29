#include <stdio.h>
#include <stdlib.h>
//total number of nodes in binary tree

typedef struct linknode *link;
struct linknode{
    int data;
    link lchild;
    link rchild;
};
typedef struct linknode ln;

ln* create(ln* node,int num){
    ln* newnode = (ln*) calloc(1,sizeof(ln));
    newnode->data = num;
    newnode->lchild = newnode->rchild = NULL;
    if(node == NULL){
        node = newnode;
        return node;
    }else{
        ln* parent = NULL;
        ln* curr = node;
        while(curr){
            while(curr && newnode->data < curr->data){
            parent = curr;
            curr = curr->lchild;
        }
        while(curr && newnode->data > curr->data){
            parent = curr;
            curr = curr->rchild;
        }
        }
        if(curr!=NULL) return node;
        else{
            if(newnode->data > parent->data){
                parent->rchild = newnode;
            }else if(newnode->data < parent->data){
                parent->lchild = newnode;
            }
            return node;
        }
    }
}
int opcount = 1;
void inorder(ln* root){
    if(root){
        opcount += 2;
        inorder(root->lchild);
        printf("%d\t",root->data);
        inorder(root->rchild);
    }else{
        opcount -= 1;
    }
    return;
}

int main(){
    printf("Enter data (enter -1) to exit :");
    ln* root = (ln*) calloc(1,sizeof(ln));
    root = NULL;
    int number;
    while(1){
        scanf("%d",&number);
        if(number == -1) break;
        root = create(root,number);
    }
    printf("\nInorder print :");
    inorder(root);
    printf("\n Opcount : %d \n",opcount);
}