#include "sendner.h"

#include <xc.h>

#define light_lamp(n, val) do { PORTAbits.RA##n = val; } while (0)
#define light_lamp0(val) light_lamp(0, val)


void send_signals(void) {
    send_signal_to_doors_and_windows();
//    send_signal_to_hick_vision();
//    send_signal_to_new_pic();
    //MSdelay(60 * 1000);
}


void send_signal_to_doors_and_windows() {
  // of course we should turn off lamp in the end, but for sending 
  // signals to doors and window it's useless logic
  ANSELA = 0;
  TRISA = 0;
  light_lamp0(1);
}