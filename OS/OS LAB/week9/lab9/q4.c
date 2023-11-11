#include<stdio.h>

struct page{
	int num;
	int clock;
	int ref;
};

int hits=0;
int faults=0;

void lru(struct page *pages, int next){
	int i;
	int flag=0;
	for(i=0;i<3;i++){
			if(pages[i].num==next){
				flag=1;
				pages[i].ref=1;
				pages[i].clock=0;
				hits++;
				for(int j=0;j<3;j++){
					if(j!=i){
						pages[j].clock+=1;
					}	
				}
			}
		}
	if(flag==1){
		return;
	}
	else{
		faults++;
		for(i=0;i<3;i++){
		if(pages[i].ref==-1){
			pages[i].num=next;
			pages[i].ref=0;
			pages[i].clock=0;
			flag=1;
			for(int j=0;j<3;j++){
				if(j!=i){
					pages[j].clock+=1;
				}
			}
			break;
		}
	}
		if(flag==1){
			return;
		}
		else{
			int clk=0;
			int rp=0;
			for(i=0;i<3;i++){
				if(pages[i].ref==1){
					pages[i].ref=0;
				}
				else{
					if(pages[i].clock>clk){
						rp=i;
						clk=pages[i].clock;
					}
				}
			}
			pages[rp].num=next;
			pages[rp].ref=0;
			pages[rp].clock=0;
			for(int j=0;j<3;j++){
					if(j!=rp){
						pages[j].clock+=1;
					}	
				}
		}
	}
}

int main(){
	struct page pages[3];
	int x=1;
	int next;
	for(int i=0;i<3;i++){
		pages[i].num=-1;
		pages[i].clock=0;
		pages[i].ref=-1;
	}
	do{
		printf("Enter 1 to enter next page, 0 to exit: \n");
		scanf("%d",&x);
		switch(x){
		case 0:
			break;
		case 1:
			printf("Enter next page required: \n");
			scanf("%d",&next);
			lru(pages,next);
			for(int i=0;i<3;i++){
				printf("%d %d %d     ",pages[i].num, pages[i].clock, pages[i].ref);
			}
			printf("\n");
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}while(x);
	printf("\n\n%d hits %d faults\n",hits,faults);
	return 0;
}