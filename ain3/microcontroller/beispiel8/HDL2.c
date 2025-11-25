#include <msp430.h>
#include "event.h"
#include "UCA1.h"
#include "HDL1.h"
#include "HDL2.h"

LOCAL Void State0(Void);
LOCAL Void State1(Void);

LOCAL struct {
   Int      cnt;
   UInt     pos;
   VoidFunc state;
} hdl2;

GLOBAL inline Void HDL2_init(Void) {
   hdl2.cnt   = 0;
   hdl2.pos   = 0;
   hdl2.state = State0;
}

LOCAL Void State0(Void) {
   if (Event_tst(EVENT_7SEG)) {
     Event_clr(EVENT_7SEG);
     hdl2.cnt   = 0;
     hdl2.pos   = 0;
     hdl2.state = State1;
     Event_set(EVENT_SPIRDY);
  }
}

LOCAL Void State1(Void) {
   if (Event_tst(EVENT_7SEG)) {
     Event_clr(EVENT_7SEG);
     hdl2.cnt++;
   }
   if (Event_tst(EVENT_SPIRDY)) {
      Event_clr(EVENT_SPIRDY);
      if (hdl2.pos GE DIGISIZE) {
         if (hdl2.cnt EQ 0) {
            hdl2.state = State0;
            return;
         }
         hdl2.cnt = 0;
         hdl2.pos = 0;
      }
      UCA1_emit(hdl2.pos + DRVWREN, digi[hdl2.pos], EVENT_SPIRDY);
      hdl2.pos++;
   }
}

GLOBAL inline Void HDL2_run(Void) {
   (*hdl2.state)();
}
