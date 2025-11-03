#include <msp430.h>
#include "..\base.h"
#include "TA0.h"

// Zeitspanne = MAX1 (2000 ms, 500 ms) = 2500 ms
// Teilungsfaktor = Timer-Clock * Zeitspanne = 1534375
// Skalierungsfaktor = 1534375 / 2^15 = 46.8254 => 48 = {/8} {/6}
// Zeitspanne = MAX2 (750 ms, 750 ms) = 1500 ms
// Teilungsfaktor = Timer-Clock * Zeitspanne = 920625
// Skalierungsfaktor = 920625 / 2^15 = 28,0952 => 32 = {/8} {/4}
// Zeitspanne = MAX3 (250 ms, 250 ms) = 500 ms
// Zeitspanne = MAX4 (500 ms, 500 ms, 1500 ms) = 2500 ms
// Teilungsfaktor = Timer-Clock * Zeitspanne = 1534375
// Skalierungsfaktor = 1534375 / 2^15 = 46.8254 => 48 = {/8} {/6}
// Zeitspanne = MAX5 (500 ms, 500 ms, 500 ms, 500 ms, 1500 ms) = 3500 ms
// Teilungsfaktor = Timer-Clock * Zeitspanne = 2148125
// Skalierungsfaktor = 2148125 / 2^15 = 65,5555 => ? = {/?} {/?} 8*8=64 thus too small
// Zeitspanne = MAX6 (500 ms, 500 ms, 500 ms, 500 ms, 500 ms, 500 ms, 1500 ms) = 4500 ms
// Teilungsfaktor = Timer-Clock * Zeitspanne = 2761875
// Skalierungsfaktor = 2761875 / 2^15 = 84,2857 => ? = {/?} {/?} 8*8=64 thus too small
// Timer-Clock = 613.75 kHz
#define HIGH     (0x8000)
#define LOW      (0x0000)

#define ACLKFRQ  (613.75e3)
#define TICK(t)  ((UInt)((ACLKFRQ * (t)) / 28.0) - 1)

typedef struct {
    const UChar state;
    const UChar ticks;
} TMusterStep;

// Basis-Tick: 250 ms. Alle Dauern sind Vielfache davon.
#define BASIS_TICK_MS 250

const TMusterStep muster1[] = {
    {1, 8},
    {0, 2},
    {0, 0}
};

const TMusterStep muster2[] = {
    {1, 3},
    {0, 3},
    {0, 0}
};

const TMusterStep muster3[] = {
    {1, 1},
    {0, 1},
    {0, 0}
};

const TMusterStep muster3[] = {
    {1, 1},
    {0, 1},
    {0, 0}
};

const TMusterStep muster4[] = {
    {0, 2},
    {1, 2},
    {0, 6},
    {0, 0}
};

const TMusterStep muster4[] = {
    {0, 2},
    {1, 2},
    {0, 6},
    {0, 0}
};

const TMusterStep muster5[] = {
    {0, 2},
    {1, 2},
    {0, 2},
    {1, 2},
    {0, 6},
    {0, 0}
};

const TMusterStep muster6[] = {
    {1, 2}, {0, 2},
    {1, 2}, {0, 2},
    {1, 2}, {0, 2},
    {1, 6},
    {0, 0}
};



LOCAL const Int *ptr;
/*
 * Man soll sich eine geeignete Datenstruktur überlegen,
 * die eine laufzeiteffiziente Ausführung der ISR ermöglicht.
 */

GLOBAL Void set_blink_muster(UInt arg) {
/*
 * Die Funktion muss so erweitert werden,
 * dass ein Blinkmuster selektiert wird.
 * Diese Lösung hängt stark von der gewählten
 * Datenstruktur ab.
 */
}

#pragma FUNC_ALWAYS_INLINE(TA0_init)
GLOBAL Void TA0_init(Void) {
   TA0CTL   = 0; // stop mode, disable and clear flags
   TA0CCTL0 = 0; // no capture mode, compare mode
                 // clear and disable interrupt flag
   TA0CCR0  = 0xFFFF;       // set up Compare Register
   TA0EX0   = TAIDEX_0;     // set up expansion register
   TA0CTL   = TASSEL__ACLK  // 613.75 kHz
            | MC__UP        // Up Mode
            | ID__1         // input divider
            | TACLR         // clear and start Timer
            | TAIE          // enable interrupt
            | TAIFG;        // set interrupt flag
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt Void TIMER0_A1_ISR(Void) {

   /*
    * Der Inhalt der ISR ist zu implementieren
    */
}
