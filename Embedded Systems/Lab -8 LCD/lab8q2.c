#include<LPC17xx.h>
#include<stdlib.h>
#include "lab8q1.h"
unsigned char Msg4[16] = {"DIE Tossing"};

int main(void){
	unsigned char num;
    /* Setting the directions as output */
    LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28; // 23-26: D0-D7, 27: RS, 28: Enable
    clear_ports();
		delay_lcd(3200);
	
		lcd_init();
      
		lcd_com(0x80);	//First line first char
		delay_lcd(800);
		lcd_puts(&Msg4[0]);	// Second line first char
		delay_lcd(800);
		while(1){
			if(!(LPC_GPIO2->FIOPIN & 1<<12)){
				num = rand()%6 + 1;
				num += 0x30;
				lcd_com(0xC0);			//convert to ascii
				delay_lcd(800);
				lcd_puts(&num);
			}
		}
}

