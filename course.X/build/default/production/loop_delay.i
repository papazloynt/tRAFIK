# 1 "loop_delay.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18F-K_DFP/1.7.134/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "loop_delay.c" 2
# 1 "./loop_delay.h" 1



void MSdelay(unsigned int val);
# 1 "loop_delay.c" 2
# 16 "loop_delay.c"
void MSdelay(unsigned int val) {
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);
}
