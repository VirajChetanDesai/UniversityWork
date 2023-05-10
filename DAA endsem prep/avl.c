#include<stdio.h>
#include<stdlib.h>

typedef struct AVLNode *anode;
struct AVLNode{
    int key;
    int height;
    anode left;
    anode right;
};
typedef struct AVLNode node;

int getHeight(node *n){
    if(n==NULL){
        return 0;
    }
    return n->height;
}

node* createNode(int key){
    node* n = (node*) mallc(sizeof(node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

int getBalanaceFactor(node* n){
    if(n==NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

node* leftRotate(node* n){
    node* x = n->right;
    node* temp = x->left;
    x->left = n;
    n->right = temp;
    x->height = max(x->left->height,x->right->height)+1; 
    n->height = max(n->left->height,n->right->height)+1;
    return x;
    //x is the new root
}

node* rightRotate(node* n){
    node* x = n->left;
    node* temp = x->right;
    x->right = n;
    n->left = temp;
    x->height = max(x->left->height,x->right->height)+1;
    n->height = max(n->left->height,n->right->height)+1;
    return x;
    //new root is x
}

node* insert(node* node,int key){
    if(node == NULL){
        return createNode(key);
    }
    if(key < node->key){
        node->left = insert(node->left,key);
    }else if(key > node->key){
        node->right = insert(node->right,key);
    }
    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
    int bf = getBalanaceFactor(node);
    //ll
    if(bf>1 && key < node->left->key){
        rightRotate(node);
    }
    //rr
    if(bf<-1 && key > node->right->key){
        leftRotate(node);
    } 
    //lr
    if(bf>1 && key > node->left->key){
        node->left = leftRotate(node->left);
        rightRotate(node);
    }
    //rl
    if(bf<-1 && key < node->right->key){
        node->right = rightRotate(node->right);
        leftRotate(node);
    }
    return node;
}

void inorder(struct AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d balance is : %d\n", root->key,getBalance(root));
        inorder(root->right);
    }
}


void main(){
    int element,check;
    node *root = NULL;
    while(1){
        printf("Insert elements:");
        scanf("%d",&element);
        root = insert(root,element);
        printf("Enter 0 to exit else add elements:");
        scanf("%d",&check);
        if(check == 0) break;
    }
    inorder(root);
}