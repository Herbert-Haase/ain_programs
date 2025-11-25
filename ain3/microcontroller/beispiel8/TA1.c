#include <msp430.h>
#include "TA1.h"
#include "event.h"

#define CNTMAX   (5)  // Max. Wert für die Hysterese

#define ACLKFRQ  (613.75e3)
#define DLY0     (20.0e-3 / (float)CNTMAX)
#define DLY1     (UInt)(75.0e-3 * ACLKFRQ)
#define DLY2     (UInt)(DLY0    * ACLKFRQ)
#define DLY3     (UInt)(25.0e-6 * ACLKFRQ)

typedef enum {S0, S1} TState;

LOCAL struct {
   Int    cnt;
   TState state;
} var;

LOCAL const struct {
   const UChar  * const port;
   const UChar          mask;
   const TEvent         msg;
} btn = {(UChar *)(&P1IN), BIT0, EVENT_BTN1};

#pragma FUNC_ALWAYS_INLINE(TA1_init)
GLOBAL inline Void TA1_init(Void) {
   var.cnt   = 0;
   var.state = S0;
   TA1CTL    = 0; // stop mode, disable and clear flags
   TA1CCTL0  = 0; // no capture mode, compare mode
                  // clear and disable interrupt flag
   TA1CCR0   = DLY1;        // set up Compare Register
   TA1EX0    = TAIDEX_0;    // set up expansion register /1
   TA1CTL    = TASSEL__ACLK // 613.75 kHz
             | MC__UP       // Up Mode
             | ID__1        // input divider /1
             | TACLR        // clear and start Timer
             | TAIE         // enable interrupt
             | 0;           // clear interrupt flag
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt Void TIMER1_A1_ISR(Void) {
   SETBIT(P3OUT, BIT4);
   CLRBIT(TA1CTL, TAIFG); // clear interrupt flag

   TA1CCR0 = DLY2;

   // ein nicht gedrückter Button ist mit 1 aktiv
   if (TSTBIT(*btn.port, btn.mask)) {
      if (--var.cnt LT 0) {
         var.cnt   = 0;
         var.state = S0;
      }
   } else if (++var.cnt GT CNTMAX-1) {
      var.cnt = CNTMAX-1;
      if (var.state EQ S0) {
         var.state = S1;
         Event_set(btn.msg); // Event
         __low_power_mode_off_on_exit();
      }
   }
   CLRBIT(P3OUT, BIT4);
}
