/*
   LCD16x2 8-bit Source File 
   http://www.electronicwings.com
 */

#include "lcd.h"
#include "loop_delay.h"

#include <stdio.h>
#include <string.h>

/****************************Functions********************************/
void LCD_Init()
{
   	LCD_Dir1 = 0x00;          /*Set PORTB as output PORT for LCD data(D0-D7) pins*/
    LCD_Dir2 = 0x00;          /*Set PORTD as output PORT LCD Control(RS,EN) Pins*/
    MSdelay(20);
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    LCD_Command(0x01);     /*clear display screen*/
    LCD_Command(0x0c);     /*display on cursor off*/
    LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
	
}

void LCD_Clear()
{
    	LCD_Command(0x01);     /*clear display screen*/
}

void LCD_Command(char cmd )
{
	ldata= cmd;            /*Send data to PORT as a command for LCD*/   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
    MSdelay(3);
}

void LCD_Char(char dat)
{
	ldata= dat;            /*Send data to LCD*/  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	NOP();
	EN=0;
//    MSdelay(1);
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);

      msg++;	
    }	
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<1)
    {
        location=(0x80) | ((pos) & 0x0f);      /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);      /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    

    LCD_String(msg);

}

void print_val_to_LCD(int8_t is_negative, float val) {
    char Temperature[10];
    
    val = (float)(val/100.00);
    if (is_negative) {
        sprintf(Temperature,"- %d C ",(int)val);
    } else {
        sprintf(Temperature,"%d C    ",(int)val);               
    }
    LCD_String_xy(1,0,Temperature);    
    MSdelay(1000);
    memset(Temperature,0,10);
}


