#include<LPC17xx.h>
unsigned char seg[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
int d[4];
unsigned int i,j;
void delay(void);

int main()
{
LPC_PINCON->PINSEL0 &= 0XFF0000FF;
LPC_PINCON->PINSEL3 = 0X0;
LPC_GPIO0->FIODIR |= 0XFF0;
LPC_GPIO1->FIODIR = 0X07800000;
LPC_PINCON->PINSEL1=0X0;

while(1)
{
unsigned int k=((LPC_GPIO0->FIOPIN & 1<<21));

if(k==0)
{
	for(d[3]=0;d[3]<16;d[3]++)
	{
		for(d[2]=0;d[2]<16;d[2]++)
		{
			for(d[1]=0;d[1]<16;d[1]++)
			{
				for(d[0]=0;d[0]<16;d[0]++)
				{
					for(i=0;i<4;i++)
					{
						LPC_GPIO1->FIOPIN=i<<23;
						LPC_GPIO0->FIOPIN=seg[d[i]]<<4;
						delay();
					}
					LPC_GPIO0->FIOCLR |= 0X00000FF0;	
				}
			}
		}
	}
}
else
{
for(d[3]=15;d[3]>=0;d[3]--)
	{
		for(d[2]=15;d[2]>=0;d[2]--)
		{
			for(d[1]=15;d[1]>=0;d[1]--)
			{
				for(d[0]=15;d[0]>=0;d[0]--)
				{
					for(i=0;i<4;i++)
					{
						LPC_GPIO1->FIOPIN=i<<23;
						LPC_GPIO0->FIOPIN=seg[d[i]]<<4;
						delay();
					}
					LPC_GPIO0->FIOCLR |= 0X00000FF0;	
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