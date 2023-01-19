#include "configuration_header_file.h"         
#include "lcd.h"
#include "ds18b20.h"
#include "sendner.h"

#define _XTAL_FREQ 8000000


void main(void)
{
  OSCCON = 0x72;   // set internal oscillator to 8MHz
  ANSELD = 0;

  int skip_first_few_step = 5;
  while(1) {   
    int  temp[2];
    calculate_tempereture(temp);
    
    // use this shit, cause for few first operation
    // next if construction is true. 
    if (skip_first_few_step) {
        skip_first_few_step--;
        continue;
    }
    
    // check only positive temperature
    if((temp[1] & 0x80)==0){
        float i = ((unsigned int)temp[1] << 8 ) + (unsigned int)temp[0];
        // if temperature > 50 celitius
        if ((int)((i * 6.25)/100.00) > 50 ) {
            send_signals();
        } 
    } 
  }
}