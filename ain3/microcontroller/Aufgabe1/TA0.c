#include "TA0.h"
#include "..\base.h"
#include <msp430.h>


#define HIGH (0x8000)
#define LOW (0x0000)
#define ACLKFRQ (613750UL)
#define GLOBAL_DIVIDER (40)

#define TICK(ms) ((UInt)((((ACLKFRQ / 1000) * (ms)) / GLOBAL_DIVIDER) - 1))

// Alle Muster verwenden denselben Teiler von 40
// Zeitspanne = MAX (ALLE_MUSTER) = 2000 ms
// Timer-Clock = 613.75 kHz
// Teilungsfaktor = Timer-Clock * Zeitspanne = 1227500
// 16 Bit-Timer: max. Schritte 2^15
// Skalierungsfaktor =  1227500 / 2^15 = 37.46 =>  = {/8} {/5}

static const Int muster1[] = {HIGH | TICK(2000), LOW | TICK(500), 0};
static const Int muster2[] = {HIGH | TICK(750), LOW | TICK(750), 0};
static const Int muster3[] = {HIGH | TICK(250), LOW | TICK(250), 0};
static const Int muster4[] = {LOW | TICK(500), HIGH | TICK(500),
                              LOW | TICK(1500), 0};
static const Int muster5[] = {LOW | TICK(500),  HIGH | TICK(500),
                              LOW | TICK(500),  HIGH | TICK(500),
                              LOW | TICK(1500), 0};
static const Int muster6[] = {
    LOW | TICK(500), HIGH | TICK(500), LOW | TICK(500),  HIGH | TICK(500),
    LOW | TICK(500), HIGH | TICK(500), LOW | TICK(1500), 0};

static const Int *const all_patterns[] = {muster1, muster2, muster3,
                                          muster4, muster5, muster6};

static const Int *ptr;
static UInt current_muster_num;


GLOBAL Void set_blink_muster(UInt arg) {
    current_muster_num = arg;
    ptr = all_patterns[current_muster_num];
}

#pragma FUNC_ALWAYS_INLINE(TA0_init)
GLOBAL inline Void TA0_init(Void) {
  current_muster_num = MUSTER1;

  TA0CTL = 0;
  TA0CCTL0 = 0;
  //TA0CCR0 = 0;

  TA0EX0 = TAIDEX_4;    // Expansion Divider /5
  TA0CTL = TASSEL__ACLK // Taktquelle
           | MC__UP     // Up Mode
           | ID__8      // Input Divider /8
           | TACLR      // Timer lÃƒÂ¶schen
           | TAIE      // Interrupts global aktivieren
           | TAIFG;

  set_blink_muster(MUSTER1);
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt Void TIMER0_A1_ISR(Void) {

  if (*ptr == 0) {
    ptr = all_patterns[current_muster_num];
  }

  UInt cnt = *ptr++;

  if (TSTBIT(cnt, HIGH)) {
    SETBIT(P1OUT, BIT2);
    CLRBIT(cnt, HIGH);
  } else {
    CLRBIT(P1OUT, BIT2);
  }

  CLRBIT(TA0CTL, TAIFG);
  TA0CCR0 = cnt;
}
