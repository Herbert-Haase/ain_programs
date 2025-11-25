#include <msp430.h>
#include "HDL1.h"
#include "event.h"

GLOBAL UChar digi[DIGISIZE];

GLOBAL inline Void HDL1_init(Void) {
   for (Int i=DIGISIZE-1; i GE 0; i--) {
      digi[(unsigned)i]  = 0;
   }
}

GLOBAL Void HDL1_run(Void) {
   if (Event_tst(EVENT_BTN1)) {
      SETBIT(P3OUT, BIT6);
      Event_clr(EVENT_BTN1);
      UInt c = 1;
      for (Int i=0; i LT DIGISIZE; i++) {
         UInt res = digi[(unsigned)i] + c;
         c = 0;
         if (res GE NUMBASE) {
            c = 1;
            res -= NUMBASE;
         }
         digi[(unsigned)i] = res;
      }
      Event_set(EVENT_7SEG);
      CLRBIT(P3OUT, BIT6);
   }
}
