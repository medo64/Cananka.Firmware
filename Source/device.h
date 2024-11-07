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


#ifndef DEVICE_H
#define DEVICE_H

#include <stdbool.h>
#include <stdint.h>
#include "app.h"

void device_init(void);

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

#endif
