#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "can.h"
#include "io.h"

typedef union {
    struct {
        uint8_t COMSTAT;
    };
    struct {
        CAN_STATUS STATUS;
    };
} CAN_RAW_STATUS;

uint16_t speed = 0;
CAN_STATE canState = CAN_STATE_CLOSED;

void can_init_internal(uint8_t brp, uint8_t prseg, uint8_t seg1ph, uint8_t seg2ph, uint8_t sjw, bool sampleThree) {
    TRISB2 = 0;
    TRISB3 = 1;
    CIOCONbits.ENDRHI = 1;  // drive Vdd when recessive
    CIOCONbits.CANCAP = 1;  // enable CAN capture

    CANCONbits.REQOP = 0b100; //set to Configuration mode
    while (CANSTATbits.OPMODE != 0b100) { Nop(); }

    BRGCON2bits.SEG2PHTS =  1; //freely programmable SEG2PH
    ECANCONbits.MDSEL = 2; //enhanced FIFO mode

    // use 8 buffers for receive (each set to receive all messages)
    RXB0CONbits.RXM1 = 1;
    RXB1CONbits.RXM1 = 1;
    B0CONbits.RXM1 = 1;
    B1CONbits.RXM1 = 1;
    B2CONbits.RXM1 = 1;
    B3CONbits.RXM1 = 1;
    B4CONbits.RXM1 = 1;
    B5CONbits.RXM1 = 1;

    // baud rate
    BRGCON1bits.BRP    = brp;          // BRP
    BRGCON2bits.PRSEG  = prseg;        // PRSEG
    BRGCON2bits.SEG1PH = seg1ph;       // SEG1PH
    BRGCON3bits.SEG2PH = seg2ph;       // SEG2PH
    BRGCON1bits.SJW    = sjw;          // SJW
    BRGCON2bits.SAM    = sampleThree;  // SAM

    CANCONbits.REQOP = 0b001; //set to sleep/disabled
    while (CANSTATbits.OPMODE != 0b001) { Nop(); }
    canState = CAN_STATE_CLOSED;
}


void can_init(uint8_t brp, uint8_t prseg, uint8_t seg1ph, uint8_t seg2ph, uint8_t sjw, bool sampleThree) {
    can_init_internal(brp, prseg, seg1ph, seg2ph, sjw, sampleThree);
    speed = 0;
}

void can_init_20k() {
    can_init_internal(59, 7, 6, 3, 0, true);  // PRSEG: 8 Tq  SEG1PH: 7 Tq  SEG2PH: 4 Tq  SJW: 1 Tq  (20 Tq  0.25%  3000m)
    speed = 20;
}

void can_init_50k() {
    can_init_internal(39, 4, 3, 1, 0, true);  // PRSEG: 5 Tq  SEG1PH: 4 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (12 Tq  0.42%  1000m)
    speed = 50;
}

void can_init_100k() {
    can_init_internal(19, 4, 3, 1, 0, true);  // PRSEG: 5 Tq  SEG1PH: 4 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (12 Tq  0.42%  700m)
    speed = 100;
}

void can_init_125k() {
    can_init_internal(15, 4, 3, 1, 0, true);  // PRSEG: 5 Tq  SEG1PH: 4 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (12 Tq  0.42%  600m)
    speed = 125;
}

void can_init_250k() {
    can_init_internal(7, 4, 3, 1, 0, true);  // PRSEG: 5 Tq  SEG1PH: 4 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (12 Tq  0.42%  200m)
    speed = 250;
}

void can_init_500k() {
    can_init_internal(3, 4, 3, 1, 0, true);  // PRSEG: 5 Tq  SEG1PH: 4 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (12 Tq  0.42%  100m)
    speed = 500;
}

void can_init_800k() {
    can_init_internal(2, 3, 2, 1, 0, true);  // PRSEG: 4 Tq  SEG1PH: 3 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (10 Tq  0.50%  50m)
    speed = 800;
}

void can_init_1000k() {
    can_init_internal(1, 5, 2, 1, 0, true);  // PRSEG: 6 Tq  SEG1PH: 3 Tq  SEG2PH: 2 Tq  SJW: 1 Tq  (12 Tq  0.42%  50m)
    speed = 1000;
}


uint16_t can_getSpeed() {
    return speed;
}


void can_open() {
    CANCONbits.REQOP = 0b000; //set to normal mode
    while (CANSTATbits.OPMODE != 0b000) { Nop(); }
    canState = CAN_STATE_OPEN;
}

void can_openListenOnly() {
    CANCONbits.REQOP = 0b011; //set to listen-only mode
    while (CANSTATbits.OPMODE != 0b011) { Nop(); }
    canState = CAN_STATE_OPEN_LISTENONLY;
}

void can_openLoopback() {
    CANCONbits.REQOP = 0b010; //set to loopback mode
    while (CANSTATbits.OPMODE != 0b010) { Nop(); }
    canState = CAN_STATE_OPEN_LOOPBACK;
}

void can_close() {
    // abort stuff in progress
    TXB0CONbits.TXABT = 0;
    TXB1CONbits.TXABT = 0;
    TXB2CONbits.TXABT = 0;

    // switch to sleep (roundabout way via config in order to avoid errata)
    CANCONbits.REQOP = 0b100; //set to configuration
    while (CANSTATbits.OPMODE != 0b100) { Nop(); }
    CANCONbits.REQOP = 0b001; //set to sleep/disabled
    while (CANSTATbits.OPMODE != 0b001) { Nop(); }

    canState = CAN_STATE_CLOSED;
}


CAN_STATE can_getState() {
    return canState;
}

bool can_isOpen() {
    return (canState != CAN_STATE_CLOSED) ? true : false;
}


CAN_STATUS can_getStatus() {
    CAN_RAW_STATUS status;
    status.COMSTAT = COMSTAT;
    return status.STATUS;
}

bool can_tryRead(CAN_MESSAGE* message) {
    if (COMSTATbits.NOT_FIFOEMPTY == 0) { return false; }

    for (uint8_t i = 0b10000; i <= 0b10111; i++) {
        ECANCONbits.EWIN = i;;  // select buffer into 0xF60 - 0xF6D
        if (RXB0CONbits.RXFUL) {
            if (RXB0SIDLbits.EXID) { //extended
                (*message).Header.ID = ((uint32_t)RXB0SIDHbits.SID << 21) | ((uint32_t)RXB0SIDLbits.SID << 18) | ((uint32_t)RXB0SIDLbits.EID << 16) | ((uint32_t)RXB0EIDHbits.EID << 8) | RXB0EIDLbits.EID;
                (*message).Flags.IsExtended = true;
            } else {
                (*message).Header.ID = ((uint32_t)RXB0SIDHbits.SID << 3) | RXB0SIDLbits.SID;
                (*message).Flags.IsExtended = false;
            }
            (*message).Flags.Length = RXB0DLCbits.DLC;
            if (RXB0CONbits.RTRRO) {
                (*message).Flags.IsRemoteRequest = true;
            } else {
                (*message).Flags.IsRemoteRequest = false;
                (*message).Data[0] = RXB0D0;
                (*message).Data[1] = RXB0D1;
                (*message).Data[2] = RXB0D2;
                (*message).Data[3] = RXB0D3;
                (*message).Data[4] = RXB0D4;
                (*message).Data[5] = RXB0D5;
                (*message).Data[6] = RXB0D6;
                (*message).Data[7] = RXB0D7;
            }
            RXB0CONbits.RXFUL = 0;
            return true;
        }
    }
    return false;
}

void can_read(CAN_MESSAGE* message) {
    while (!can_tryRead(message));
}


bool can_tryWrite(CAN_MESSAGE message) {
    for (uint8_t i = 0b00011; i <= 0b00101; i++) {
        ECANCONbits.EWIN = i;;  // select TX buffer into 0xF60 - 0xF6D (RXB0)

        if ((RXB0CON & 0b00001000) == 0) {  // !TXBnCON.TXREQ
            if (message.Flags.IsExtended) {
                RXB0EIDLbits.EID = (uint8_t)(message.Header.ID & 0xFF);         // TXBnEIDL
                RXB0EIDHbits.EID = (uint8_t)((message.Header.ID >> 8) & 0xFF);  // TXBnEIDH
                RXB0SIDLbits.EID = (uint8_t)((message.Header.ID >> 16) & 0x03);  // TXBnSIDL
                RXB0SIDLbits.SID = (uint8_t)((message.Header.ID >> 18) & 0x07);  // TXBnSIDL
                RXB0SIDHbits.SID = (uint8_t)(message.Header.ID >> 21);           // TXBnSIDH
            } else {
                RXB0SIDLbits.SID = (uint8_t)(message.Header.ID & 0x07);          // TXBnSIDL
                RXB0SIDHbits.SID = (uint8_t)(message.Header.ID >> 3);            // TXBnSIDH
            }

            RXB0SIDLbits.EXID = message.Flags.IsExtended;       // TXBnSIDL.EXID
            RXB0DLCbits.DLC = message.Flags.Length;             // TXBnDLC
            RXB0DLCbits.RXRTR = message.Flags.IsRemoteRequest;  // TXBnDLC.TXRTR

            RXB0D0 = message.Data[0];  //TXBnD0
            RXB0D1 = message.Data[1];  //TXBnD1
            RXB0D2 = message.Data[2];  //TXBnD2
            RXB0D3 = message.Data[3];  //TXBnD3
            RXB0D4 = message.Data[4];  //TXBnD4
            RXB0D5 = message.Data[5];  //TXBnD5
            RXB0D6 = message.Data[6];  //TXBnD6
            RXB0D7 = message.Data[7];  //TXBnD7

            RXB0CON |= 0b00001000;  // TXBnCON.TXREQ = 1
            return true;
        }
    }

    return false;
}

bool can_write(CAN_MESSAGE message) {
    while (!can_tryWrite(message)) {
        if (COMSTATbits.TXBO || COMSTATbits.TXBP) { return false; } //break away if device is bus passive
    }
    return true;
}
