#include<stdio.h>
#include<stdlib.h>

typedef struct linknode *link;
struct linknode{
    int element;
    link left;
    link right;
};
typedef struct linknode ln;

int height(ln *root){
    if(root == NULL){
        return 1;
    }
    return 1+max(height(root->left),height(root->right));
}

int diameter(ln *root){
    return 1 + height(root->left) + height(root->right);
}

void main(){
}