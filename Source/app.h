#pragma once

// Select hardware revision
//#define CANANKA_REVISION_A
//#define CANANKA_REVISION_B
//#define CANANKA_REVISION_C
//#define CANANKA_REVISION_D
#define CANANKA_REVISION_E

// Select hardware type
#define CANANKA_TYPE_FULL
//#define CANANKA_TYPE_RJ45
//#define CANANKA_TYPE_MINI
//#define CANANKA_TYPE_FEC


// Software version
#define SOFTWARE_VERSION_MAJOR  2
#define SOFTWARE_VERSION_MINOR  0


#define _XTAL_FREQ 48000000


// CONFIG1L
#pragma config RETEN = OFF      // VREG Sleep Enable bit (Ultra low-power regulator is Disabled (Controlled by REGSLP bit))
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = HIGH   // SOSC Power Selection and mode Configuration bits (High Power SOSC circuit selected)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config FOSC = HS1       // Oscillator (HS oscillator (Medium power, 4 MHz - 16 MHz))
#pragma config PLLCFG = ON      // PLL x4 Enable bit (Enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = ON      // Power Up Timer (Enabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 0         // Brown-out Reset Voltage bits (3.0V)
#pragma config BORPWR = HIGH    // BORMV Power level (BORMV set to high power level)

// CONFIG2H
#pragma config WDTEN = SWDTDIS  // Watchdog Timer (WDT enabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

// CONFIG3H
#pragma config CANMX = PORTB    // ECAN Mux bit (ECAN TX and RX pins are located on RB2 and RB3, respectively)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = OFF      // Master Clear Enable (MCLR Disabled, RE3 Enabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)
#pragma config DEBUG = OFF      // Background Debugger (Background Debugger disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-01FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 02000-03FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 04000-05FFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 06000-07FFF (Disabled)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-01FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 02000-03FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 04000-05FFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 06000-07FFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protect 00800-01FFF (Disabled)
#pragma config EBTR1 = OFF      // Table Read Protect 02000-03FFF (Disabled)
#pragma config EBTR2 = OFF      // Table Read Protect 04000-05FFF (Disabled)
#pragma config EBTR3 = OFF      // Table Read Protect 06000-07FFF (Disabled)

// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protect Boot (Disabled)


#include <xc.h>


#define interrupt_enable()   GIE = 1
#define interrupt_disable()  GIE = 0
#define wait_short(void)     __delay_ms(113)

void init(void);


// | A3 | A5 | B0 | B1 | B4 | Type          | Revision  | PIC Clock | UART Clock | Termination | Power Supply   |
// |----|----|----|----|----|---------------|-----------|-----------|------------|-------------|----------------|
// | X  | X  | L  | H  | H  | Standard      | 3 (A)     | Crystal   | PIC        | No          | No             | +
// | L  | L  | L  | L  | H  | Mini          | 4 (D)     | MCP2221A  | MCP2221A   | Yes         | Yes (5V)       | +
// | L  | L  | H  | L  | H  | Framework     | 4 (D)     | MCP2221A  | MCP2221A   | Yes         | No  (5V)       | +
// | L  | L  | H  | H  | H  | Mini          | 1 (A B C) | MCP2221   | MCP2221    | Yes         | Yes            | + + +
// | L  | H  | L  | L  | H  | Standard      | 4 (D)     | Crystal   | MCP2221A   | No          | No             |
// | L  | H  | L  | H  | H  | Standard      | 3 (C)     | Crystal   | PIC        | No          | No             | +
// | L  | H  | H  | H  | H  | Standard      | 2 (B)     | Crystal   | PIC        | No          | No             | +
// | H  | H  | L  | L  | H  | Standard/RJ45 | 4 (D)     | Crystal   | MCP2221A   | No          | No             | +
// | H  | H  | L  | H  | H  | Standard/RJ45 | 3 (C)     | Crystal   | PIC        | No          | No             | +
// | H  | H  | H  | H  | H  | Standard/RJ45 | 2 (B)     | Crystal   | PIC        | No          | No             | +
// | L  | H  | L  | L  | L  | Standard      | 5 (E)     | Crystal   | MCP2221A   | No          | No             | +
// | L  | L  | L  | L  | L  | Mini          | 5 (E)     | MCP2221A  | MCP2221A   | Yes         | Yes (5V/400mA) | +
// | H  | L  | L  | L  | L  | Framework     | 5 (E)     | MCP2221A  | MCP2221A   | Yes         | No             | +

#if defined(CANANKA_REVISION_A) && !defined(CANANKA_REVISION_B) && !defined(CANANKA_REVISION_C) && !defined(CANANKA_REVISION_D) && !defined(CANANKA_REVISION_E)
    #define device_getMajor()  1
#elif !defined(CANANKA_REVISION_A) && defined(CANANKA_REVISION_B) && !defined(CANANKA_REVISION_C) && !defined(CANANKA_REVISION_D) && !defined(CANANKA_REVISION_E)
    #define device_getMajor()  2
#elif !defined(CANANKA_REVISION_A) && !defined(CANANKA_REVISION_B) && defined(CANANKA_REVISION_C) && !defined(CANANKA_REVISION_D) && !defined(CANANKA_REVISION_E)
    #define device_getMajor()  3
#elif !defined(CANANKA_REVISION_A) && !defined(CANANKA_REVISION_B) && !defined(CANANKA_REVISION_C) && defined(CANANKA_REVISION_D) && !defined(CANANKA_REVISION_E)
    #define device_getMajor()  4
#elif !defined(CANANKA_REVISION_A) && !defined(CANANKA_REVISION_B) && !defined(CANANKA_REVISION_C) && !defined(CANANKA_REVISION_D) && defined(CANANKA_REVISION_E)
    #define device_getMajor()  5
#else
    #error "An unique device revision has to be defined"
#endif

#if defined(CANANKA_TYPE_FULL) && !defined(CANANKA_TYPE_RJ45) && !defined(CANANKA_TYPE_MINI) && !defined(CANANKA_TYPE_FEC)
    #define device_getMinor()  0
#elif !defined(CANANKA_TYPE_FULL) && defined(CANANKA_TYPE_RJ45) && !defined(CANANKA_TYPE_MINI) && !defined(CANANKA_TYPE_FEC)
    #define device_getMinor()  1
#elif !defined(CANANKA_TYPE_FULL) && !defined(CANANKA_TYPE_RJ45) && defined(CANANKA_TYPE_MINI) && !defined(CANANKA_TYPE_FEC)
    #define device_getMinor()  2
#elif !defined(CANANKA_TYPE_FULL) && !defined(CANANKA_TYPE_RJ45) && !defined(CANANKA_TYPE_MINI) && defined(CANANKA_TYPE_FEC)
    #define device_getMinor()  3
#else
    #error "An unique device type has to be defined"
#endif

#if defined(CANANKA_REVISION_A) && defined(CANANKA_TYPE_FULL)
    #define device_supportsPower()        false
    #define device_supportsTermination()  false
    #define device_needsClockOut()        true
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         true
#elif defined(CANANKA_REVISION_A) && defined(CANANKA_TYPE_MINI)
    #define device_supportsPower()        true
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         false
    #define device_supports460K()         false
    #define device_supports920K()         false
#elif defined(CANANKA_REVISION_B) && (defined(CANANKA_TYPE_FULL) || defined(CANANKA_TYPE_RJ45))
    #define device_supportsPower()        false
    #define device_supportsTermination()  false
    #define device_needsClockOut()        true
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         true
#elif defined(CANANKA_REVISION_B) && defined(CANANKA_TYPE_MINI)
    #define device_supportsPower()        true
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         false
    #define device_supports460K()         false
    #define device_supports920K()         false
#elif defined(CANANKA_REVISION_C) && (defined(CANANKA_TYPE_FULL) || defined(CANANKA_TYPE_RJ45))
    #define device_supportsPower()        false
    #define device_supportsTermination()  false
    #define device_needsClockOut()        true
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         true
#elif defined(CANANKA_REVISION_C) && defined(CANANKA_TYPE_MINI)
    #define device_supportsPower()        true
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         false
    #define device_supports460K()         false
    #define device_supports920K()         false
#elif defined(CANANKA_REVISION_D) && (defined(CANANKA_TYPE_FULL) || defined(CANANKA_TYPE_RJ45))
    #define device_supportsPower()        false
    #define device_supportsTermination()  false
    #define device_needsClockOut()        false
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         false
#elif defined(CANANKA_REVISION_D) && defined(CANANKA_TYPE_MINI)
    #define device_supportsPower()        true
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         false
#elif defined(CANANKA_REVISION_D) && defined(CANANKA_TYPE_FEC)
    #define device_supportsPower()        false
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         false
#elif defined(CANANKA_REVISION_E) && defined(CANANKA_TYPE_FULL)
    #define device_supportsPower()        false
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         true
    #define device_supports460K()         true
    #define device_supports920K()         true
#elif defined(CANANKA_REVISION_E) && (defined(CANANKA_TYPE_MINI) || defined(CANANKA_TYPE_FEC))
    #define device_supportsPower()        false
    #define device_supportsTermination()  true
    #define device_needsClockOut()        false
    #define device_supports230K()         false
    #define device_supports460K()         false
    #define device_supports920K()         false
#else
    #error "Unrecognized device properties"
#endif
