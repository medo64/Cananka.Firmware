#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "device.h"

void device_init() {
    nRBPU = 0; //enable port B pull-ups
    WPUB0 = 1; WPUB1 = 1; WPUB4 = 1;
    TRISA3 = 1; TRISA5 = 1; TRISB0 = 1;  TRISB1 = 1; TRISB4 = 1;
    ANSEL3 = 0; ANSEL4 = 0; ANSEL10 = 0; ANSEL8 = 0; ANSEL9 = 0;
}
