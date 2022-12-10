#include <xc.h>


void light_lamp(int num) {
    switch (num) {
        case 0: 
            PORTAbits.RA0 = 0;
            PORTBbits.RB0 = 1;
            break;
        case 1: 
            PORTBbits.RB0 = 0;
            PORTBbits.RB1 = 1;
            break;
        case 2: 
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 1;
            break;
        case 3: 
            PORTBbits.RB2 = 0;
            PORTBbits.RB3 = 1;
            break;
        case 4: 
            PORTBbits.RB3 = 0;
            PORTBbits.RB4 = 1;
            break;
        case 5: 
            PORTBbits.RB4 = 0;
            PORTBbits.RB5 = 1;
            break;
        case 6: 
            PORTBbits.RB5 = 0;
            PORTAbits.RA1 = 1;
            break;    
    }
}

void main() {
    TRISB= 0x00; //Makes all bits on PORTB outputs
    ADCON0= 0x00; //Turns off the ADC
    ADCON1= 0x0F; //Makes all pins on PORTA And PORTB digital
    OSCCON= 0b01110100; //sets internal oscillator to 8MHz stable
    T0CON= 0x87;
    TMR0= 0;

    int counter = 0;
    while (TMR0 < 7812) {
        light_lamp(counter);
        counter++;
        TMR0 = 0; 
    } 

    return;
}
