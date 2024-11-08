#include <xc.h>
#include "app.h"

void io_init() {
    LC5 = 0;     // Out: LED (~on)
    TRISC5 = 0;

    LC4 = 1;     // Out: Termination (~off)
    TRISC4 = 0;

    LB5 = 1;     // Out: External Power (~off)
    TRISB5 = 0;

    TRISC2 = 0;  // In: USB Enabled
}
