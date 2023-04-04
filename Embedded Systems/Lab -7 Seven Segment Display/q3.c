#include<LPC17xx.h>
unsigned char tohex[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int arr[4]={0,0,0,0};
unsigned int i,j;
void delay(void);

int main()
{
//LPC_PINCON->PINSEL0 &= 0xFF0000FF; 
//LPC_PINCON->PINSEL3 &= 0xFFC03FFF;
//LPC_PINCON->PINSEL4 &= 0xFCFFFFFF;
//LPC_GPIO2->FIODIR &= 0XFFFFFFFE; //12TH PIN OF PORT 2 USED AS SWITCH
//LPC_PINCON->PINSEL1 &= 0xFFFFF3FF;
LPC_GPIO0->FIODIR |= 0XFF0;
LPC_GPIO1->FIODIR |=0XF<<23;
while(1)
{
if(LPC_GPIO0->FIOPIN & 1<<21)
{
for(arr[3]=9;arr[3]>=0;arr[3]--)
{
	for(arr[2]=9;arr[2]>=0;arr[2]--)
	{
		for(arr[1]=9;arr[1]>=0;arr[1]--)
		{
			for(arr[0]=9;arr[0]>=0;arr[0]--)
			{
				for(i=0;i<4;i++)
				{
					LPC_GPIO1->FIOPIN=i<<23;
					LPC_GPIO0->FIOPIN=tohex[arr[i]]<<4;
					delay();
				}
				delay();
				//LPC_GPIO0->FIOCLR |= 0x00000FF0;
			}
		}
	}
	}
}
else
{
for(arr[3]=0;arr[3]<=9;arr[3]++)
{
	for(arr[2]=0;arr[2]<=9;arr[2]++)
	{
		for(arr[1]=0;arr[1]<=9;arr[1]++)
		{
			for(arr[0]=0;arr[0]<=9;arr[0]++)
			{
				for(i=0;i<4;i++)
				{
					LPC_GPIO1->FIOPIN=i<<23;
					LPC_GPIO0->FIOPIN=tohex[arr[i]]<<4;
					delay();
				}
				delay();
				//LPC_GPIO0->FIOCLR |= 0x00000FF0;
			}
		}
	}
	
}
}
}
}

void delay(void)
{
unsigned int j;
for(j=0;j<10000;j++);
}