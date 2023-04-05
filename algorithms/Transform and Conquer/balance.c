#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct linknode *link;
struct linknode{
	int data;
	link llink;
	link rlink;
};
typedef struct linknode ln;

int max(int a, int b){
	return (a>b)?a:b;
}

int height(ln* node){
	if(node == NULL){
		return -1;
	}
	return 1 + max(height(node->llink),height(node->rlink));
}

int balanceFactor(ln* node){
	return height(node->llink) - height(node->rlink);
}

ln* create (ln* node,int x){
	if(node==NULL){
		node = (ln*) calloc(1,sizeof(ln));
		node->data = x;
		node->llink = NULL;
		node->rlink = NULL;
	}else if(x > node->data){
		node->rlink = create(node->rlink,x);
	}else if(x < node->data){
		node->llink = create(node->llink,x);
	}else{
		printf("Duplicate Node");
		return node;
	}
	return node;
}

void inorder(ln* node){
	if(node!=NULL){
		inorder(node->llink);
		printf("\n%d with balance factor : %d",node->data,balanceFactor(node));
		inorder(node->rlink);
	}
}

void main(){
	int element,check;
	ln* root = NULL;
	while(1){
		printf("Insert elements:");
		scanf("%d",&element);
		root = create(root,element);
		printf("Enter 0 to exit else add elements:");
		scanf("%d",&check);
		if(check == 0) break;
	}
	inorder(root);
	printf("\nHeight of tree : %d\n",height(root));
}