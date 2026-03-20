#include <msp430.h> 
#include "..\base.h"
#include "event.h"
#include "TA0.h"
#include "UCA1.h"

#define BASE     10
#define DIGISIZE  4

LOCAL UChar digi[DIGISIZE];

LOCAL Void State0(Void);
LOCAL Void State1(Void);
LOCAL Void State2(Void);

LOCAL struct {
   Int      cnt;
   UInt     pos;
   VoidFunc state;
} hdl2;

// DCO mit 8.0 MHz
// ACLK  := DCO /  8 =   1.0 MHz
// SMCLK := DCO / 32 = 250.0 kHz
// MCLK  := DCO /  1 =   8.0 MHz
GLOBAL Int _system_pre_init(Void) {
   // stop watchdog timer
   WDTCTL = WDTPW + WDTHOLD;
   CSCTL0_H = CSKEY_H;    // enable clock system
   CSCTL1 = DCOFSEL_3;    // DCO frequency = 8.0 MHz
                          // select clock sources
   CSCTL2 = SELA__DCOCLK  // ACLK  <- DCO
          | SELS__DCOCLK  // SMCLK <- DCO
          | SELM__DCOCLK; // MCLK  <- DCO
                          // set frequency divider
   CSCTL3 = DIVA__8       // ACLK  : /8
          | DIVS__32      // SMCLK : /32
          | DIVM__1;      // MCLK  : /1
   CSCTL4 = XT1OFF        // XT1 disabled
          | XT2OFF;       // XT2 disabled
   CSCTL5 = 0;            // disable and clear fault flags
   CSCTL6 = 0;            // disable conditional requests
   CSCTL0_H = 0;          // disable clock system
   return 0;
}

#define VAL_16BIT(arg1, arg2) ((unsigned)(((arg1) << 8) | (arg2)))

#pragma FUNC_ALWAYS_INLINE(GPIO_init)
LOCAL Void GPIO_init(Void) {
   // Port 3: Pin 7 => output, TEST4
   // Port 3: Pin 6 => output, TEST3
   // Port 3: Pin 5 => output, TEST2
   // Port 3: Pin 4 => output, TEST1
   // Port 2: Pin 7 => output, LED1, idle Low
   // Port 1: Pin 2 => output, LED2, idle Low
   // Port 2: Pin 3 => output, SPI.SEL, idle High
   // Port 2: Pin 4, 5 and 6 => SPI

   //                   Port2       Port1
   //               Bit 76543210    76543210
   PAOUT  = VAL_16BIT(0b00001000, 0b00000000); // set up outputs
   PADIR  = VAL_16BIT(0b10001000, 0b00000100); // direction, set outputs
   PAIFG  = VAL_16BIT(0b00000000, 0b00000000); // clear all interrupt flags
   PAIE   = VAL_16BIT(0b00000000, 0b00000000); // disable all GPIO interrupts
   PASEL0 = VAL_16BIT(0b00000000, 0b00000000);
   PASEL1 = VAL_16BIT(0b01110000, 0b00000000);
   PAREN  = VAL_16BIT(0b00000000, 0b00000000); // without pull up

   //                   Port4       Port3
   //               Bit 76543210    76543210
   PBOUT  = VAL_16BIT(0b00000000, 0b00000000); // clear all outputs
   PBDIR  = VAL_16BIT(0b00000000, 0b11110000); // direction, set outputs
   PBIFG  = VAL_16BIT(0b00000000, 0b00000000); // clear all interrupt flags
   PBIE   = VAL_16BIT(0b00000000, 0b00000000); // disable all GPIO interrupts
   PBSEL0 = VAL_16BIT(0b00000000, 0b00000000);
   PBSEL1 = VAL_16BIT(0b00000000, 0b00000000);
   PBREN  = VAL_16BIT(0b00000000, 0b00000000); // without pull up
}

// -------------- Handler1 -------------------------

#pragma FUNC_ALWAYS_INLINE(Handler1_init)
LOCAL Void Handler1_init(Void) {
   for (Int i=DIGISIZE-1; i GE 0; i--) {
      digi[(unsigned)i] = 0;
   }
}

LOCAL Void Handler1(Void) {
    if (Event_tst(EVENT_INCR)) {
      Event_clr(EVENT_INCR);
      UInt c = 1;
      for (Int i=0; i LT DIGISIZE; i++) {
         UInt res = digi[(unsigned)i] + c;
         c = 0;
         if (res GE BASE) {
            c = 1;
            res -= BASE;
         }
         digi[(unsigned)i] = res;
      }
      Event_set(EVENT_7SEG);
   }
}

// -------------- Handler2 -------------------------

#pragma FUNC_ALWAYS_INLINE(Handler2_init)
LOCAL Void Handler2_init(Void) {
   hdl2.state = State0;
   UCA1_emit(4 + 0x0008, 0x0002, EVENT_SPIRDY); // Display enable
}

LOCAL Void State0(Void) {
   if (Event_tst(EVENT_SPIRDY)) {
      Event_clr(EVENT_SPIRDY);
      hdl2.state = State1;
      Event_set(EVENT_7SEG);
      // clear and start Timer, enable timer interrupt
      SETBIT(TA0CTL, TACLR | TAIE);
   }
}

LOCAL Void State1(Void) {
   if (Event_tst(EVENT_7SEG)) {
      Event_clr(EVENT_7SEG);
      hdl2.pos   = 0;
      hdl2.state = State2;
      Event_set(EVENT_SPIRDY);
   }
}

LOCAL Void State2(Void) {
   if (Event_tst(EVENT_SPIRDY)) {
      Event_clr(EVENT_SPIRDY);
      if (hdl2.pos GE DIGISIZE) {
         hdl2.state = State1;
         return;
      }
      UCA1_emit(hdl2.pos + 0x0008, digi[hdl2.pos], EVENT_SPIRDY);
      hdl2.pos++;
   }
}

LOCAL Void Handler2(Void) {
   (*hdl2.state)();
}

/**
 * main.c
 */

GLOBAL Void main(Void) {
   GPIO_init();   // set up Ports
   Event_init();  //
   UCA1_init();   // set up SPI
   TA0_init();    // set up Timer

   Handler1_init();
   Handler2_init();

   while(TRUE) {
      Event_wait();
      Handler1();
      Handler2();
      if (Event_err()) {
         SETBIT(P1OUT, BIT2); // LED on
      }
   }
}

