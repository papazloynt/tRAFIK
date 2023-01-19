#include "loop_delay.h"

//void delay_us(int useconds)
//{
//int s;
//for (s=0; s<useconds;s++);
//}
//
//void delay_ms(int j)
//{
//	unsigned char i;
//	for(;j;j--)
//	for(i=122;i<=0;i--);
//}

void MSdelay(unsigned int val) {
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
}