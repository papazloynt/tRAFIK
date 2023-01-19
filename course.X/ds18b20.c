#include "ds18b20.h"
#include "loop_delay.h"

#include <xc.h>

#define DQ PORTDbits.RD5
#define DQ_TRIS TRISDbits.TRISD5

#define _XTAL_FREQ 8000000

//Each communication through DS18b20 begin with a reset pulse. This is use for resetting Ds18b20 sensor.

unsigned char ow_reset(void)
{
    DQ_TRIS = 0; // Tris = 0 (output)
	DQ = 0; // set pin# to low (0)
	__delay_us(480); // 1 wire require time delay
	DQ_TRIS = 1; // Tris = 1 (input)
	__delay_us(60); // 1 wire require time delay
	
		if (DQ == 0) // if there is a presence pluse
		{ 
		__delay_us(480);
		return 0; // return 0 ( 1-wire is presence)
		} 
		else 
		{
		__delay_us(480);
		return 1; // return 1 ( 1-wire is NOT presence)
		}

} // 0=presence, 1 = no part

// This is use for reading bit from ds18b20

unsigned char read_bit(void)
{
	unsigned char i;
	DQ_TRIS = 1;
    DQ = 0; // pull DQ low to start timeslot
	DQ_TRIS = 1;
    DQ = 1; // then return high
	for (i=0; i<3; i++); // delay 15us from start of timeslot
	return(DQ); // return value of DQ line
}

unsigned char read_byte(void)
{ 
    char i,result = 0;
	DQ_TRIS = 1; // TRIS is input(1)
		for(i = 0; i < 8; i++)
		{
		DQ_TRIS = 0; // TRIS is output(0)
		DQ = 0; // genarate low pluse for 2us
		__delay_us(2);
		DQ_TRIS = 1; // TRIS is input(1) release the bus
		if(DQ != 0) 
		result |= 1<<i;
		__delay_us(60); // wait for recovery time
		}
	return result;
}

//writes a bit to the one-wire bus, passed in bitval


void write_bit(char bitval)
{
	DQ_TRIS = 0;
    DQ = 0; // pull DQ low to start timeslot
	if(bitval==1) DQ =1; // return DQ high if write 1
	__delay_us(5); // hold value for remainder of timeslot
    DQ_TRIS = 1;
	DQ = 1;
}// Delay provides 16us per loop, plus 24us. Therefore delay(5) = 104us

void write_byte(char val)
{
    char i;
    DQ_TRIS = 1; // set pin# to input (1)
	
		for(i = 0; i < 8; i++)
		{
			if((val & (1<<i))!= 0) 
			{
			// write 1
			DQ_TRIS = 0; // set pin# to output (0)
			DQ = 0; // set pin# to low (0)
			__delay_us(1); // 1 wire require time delay
			DQ_TRIS = 1; // set pin# to input (release the bus)
			__delay_us(60); // 1 wire require time delay
			} 
			else 
			{
			//write 0
			DQ_TRIS = 0; // set pin# to output (0)
			DQ = 0; // set pin# to low (0)
			__delay_us(60); // 1 wire require time delay
			DQ_TRIS = 1; // set pin# to input (release the bus)
			}
		}

}


#define skip_rom 0xCC
#define convert_temp 0x44 
#define write_scratchpad 0x4E
#define resolution_12bit 0x7F
#define read_scratchpad 0xBE

// array[0] - TEMP_LOW
// array[1] - TEMP_HIGH
void calculate_tempereture(int* temp) { 
    ow_reset();
    
    write_byte(write_scratchpad);
    write_byte(0);
    write_byte(0);
    write_byte(resolution_12bit); // 12-?????? ??????????
    
    ow_reset();
    
    write_byte(skip_rom); 
    write_byte(convert_temp); 
    while (read_byte()==0xff);
    MSdelay(500);
    
    ow_reset();
    
    write_byte(skip_rom);
    write_byte(read_scratchpad);
    
    temp[0] = read_byte();
    temp[1] = read_byte();
}