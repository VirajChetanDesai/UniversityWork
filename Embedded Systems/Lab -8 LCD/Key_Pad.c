#include <LPC17xx.h>
# include "lcd-disp1.c"     // use all the functions of lcd program
 void scan(void);
 unsigned char Msg1[13] = "KEY PRESSED=";
 unsigned char row, flag, key;
 unsigned long int i, var1, temp3;
 unsigned char SCAN_CODE[16] = {0x11,0x21,0x41,0x81,
								0x12,0x22,0x42,0x82,
								0x14,0x24,0x44,0x84,
								0x18,0x28,0x48,0x88};

 unsigned char ASCII_CODE[16] = {'0','1','2','3',
								 '4','5','6','7',
								 '8','9','A','B',
								 'C','D','E','F'};

 int main(void)
 {
	LPC_GPIO2->FIODIR |= 0x00003C00; //made output P2.10 to P2.13 (rows)
	//LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26 (cols)  //not required since it is by default

	lcd_init();
	lcd_comdata(0x80, 0); //First line first char
	delay_lcd(800);
	lcd_puts(&Msg1[0]);	 //display the messsage

	while(1)
	{
		while(1) // constantly checks wheather key is being pressed or not
		{
			for(row=1;row<5;row++)
			{
				if(row == 1)
				var1 = 0x00000400; // P2.10 = 1
				else if(row == 2)
				var1 = 0x00000800; // P2.11 = 1
				else if(row == 3)
				var1 = 0x00001000; // P2.12 = 1
				else if(row == 4)
				var1 = 0x00002000; // P2.13 = 1
			
				LPC_GPIO2->FIOCLR = 0x00003C00;  //first clear the port to send appropriate value 
				LPC_GPIO2->FIOSET = var1;        //enabling the row (Here we know which row is being pressed)
				flag = 0;
				scan();         //scan for which key being pressed in the enabled row
				if(flag == 1)
				break;
			}  
			if(flag == 1)
			break;
		} //2nd while(1)
		for(i=0;i<16;i++)                        //get the ascii code for display
		{
			if(key == SCAN_CODE[i])
			{
				key = ASCII_CODE[i];
				break;
			}   
		} 
		lcd_comdata(0xC0, 0);     //display in the second line
		delay_lcd(800);
		lcd_puts(&key);
	}//end 1st while (1)
 }//end main

 void scan(void)
 {
	temp3 = LPC_GPIO1->FIOPIN;	
	temp3 &= 0x07800000;   //&= this extracts P1.23 to P1.26 values. OR Check if any key pressed in the enabled row
	if(temp3 != 0x00000000)
	{	
			flag = 1;
			temp3 >>= 19;	// Shifted to come at Higher Nibble of byte (Px.23 to Px.0)
			var1 >>= 10;	//shifted to come at Lower Nibble of byte (Px.23 to Px.0)
			key = temp3|var1;	//get SCAN_CODE
	}
 } 
