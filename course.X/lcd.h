#ifndef ICD
#define	ICD

#include <xc.h> // include processor files - each processor file is guarded.  

#define RS LATD0                    /*PORT 0 pin is used for Register Select*/
#define EN LATD1                    /*PORT 1 pin is used for Enable*/
#define ldata LATB                  /*PORT is used for transmitting data to LCD*/
#define LCD_Dir1 TRISD
#define LCD_Dir2 TRISB

void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void print_val_to_LCD(int8_t is_negative, float val);
void LCD_String_xy(char ,char ,const char*);

#endif	/* ICD */

