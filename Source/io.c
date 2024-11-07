#include <xc.h>

void io_init() {
    LC5 = 0;     // Out: LED
    TRISC5 = 0;

    LC4 = 1;     // Out: Termination
    TRISC4 = 0;

    LB5 = 1;     // Out: Power
    TRISB5 = 0;

    LC2 = 1;      // Out: Enabled
    TRISC2 = 0;
}
