#include<LPC17xx.h>
unsigned int i=0x00;
unsigned char array_dec[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int dig_value[4]={4,3,2,1};
unsigned int disp_select[4]={0,1,2,3};
void delay(void);
void display(void);

int main(void) {
	SystemInit();
	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR |= 0XFF<<4;
	LPC_GPIO1->FIODIR |= 0XF<<23;
	while(1) {
		delay();
		for(i=0;i<4;i++) {
			display();
			delay();
		}
	}
}
void display(void) {
	LPC_GPIO1->FIOPIN = disp_select[i]<<23;
	LPC_GPIO0->FIOPIN = array_dec[dig_value[i]]<<4;
}
void delay(void) {
	unsigned int i;
	for(i=0;i<1000;i++);
}