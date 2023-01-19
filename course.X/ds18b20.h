#ifndef DS18B20
#define	DS18B20

void delay_us(int useconds);
void delay_ms(int j);
unsigned char ow_reset(void);
unsigned char read_bit(void);
unsigned char read_byte(void);
void write_bit(char bitval);
void write_byte(char val);
unsigned char * ReadTemp();
void calculate_tempereture(int* temp);

#endif	/* DS18B20 */
