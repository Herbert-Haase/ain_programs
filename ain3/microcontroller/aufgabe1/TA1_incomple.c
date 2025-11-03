#include "..\base.h"
#include "TA1.h"
#include "event.h"
#include <msp430.h>

#define NUM_BUTTONS 2 // Anzahl der zu verwaltenden Tasten
#define CNTMAX 5      // Entprell-Zähler: 5 * 5.3ms = 26.5ms
#define ACLKFRQ 613750UL

// Zustand für die Entprell-Zustandsmaschine
typedef enum { S0, S1 } TState;

// Struktur, die den Zustand jeder Taste speichert
LOCAL struct {
  Int cnt;
  TState state;
} debounce_state[NUM_BUTTONS];

// Struktur, die die Hardware-Konfiguration jeder Taste beschreibt
LOCAL const struct {
  const UChar *const port; // Zeiger auf das Port-Eingangsregister (z.B. P1IN)
  const UChar mask;        // Bitmaske des Pins (z.B. BIT0)
  const TEvent msg;        // Zugehöriges Event (z.B. EVENT_BTN1)
} button_config[NUM_BUTTONS] = {
    {(UChar *)(&P1IN), BIT0, EVENT_BTN1}, // Konfiguration für BTN1 auf P1.0
    {(UChar *)(&P1IN), BIT1, EVENT_BTN2}  // Konfiguration für BTN2 auf P1.1
};

#pragma FUNC_ALWAYS_INLINE(TA1_init)
GLOBAL Void TA1_init(Void) {
  TA1CTL = 0;   // stop mode
  TA1CCTL0 = 0; // compare mode

  // Timer auf ca. 5ms für die Tastenabfrage konfigurieren
  // Zeit = (CCR0 + 1) / (ACLKFRQ / ID)
  // CCR0 = (Zeit * ACLKFRQ / ID) - 1
  // CCR0 = (5e-3 * 613750 / 1) - 1 = 3067.75 => 3068
  TA1CCR0 = 3068;
  TA1EX0 = TAIDEX_0;    // Teiler /1
  TA1CTL = TASSEL__ACLK // 613.75 kHz
           | MC__UP     // Up Mode
           | ID__1      // Teiler /1
           | TACLR      // Timer löschen
           | TAIE;      // Interrupt aktivieren
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt Void TIMER1_A1_ISR(Void) {
  UInt i;

  // Schleife über alle definierten Tasten
  for (i = 0; i < NUM_BUTTONS; i++) {
    // Annahme: Taste nicht gedrückt -> Pin ist HIGH (interner/externer Pull-up)
    //           Taste gedrückt      -> Pin ist LOW

    // Fall 1: Taste ist NICHT gedrückt
    if (TSTBIT(*button_config[i].port, button_config[i].mask)) {
      if (--debounce_state[i].cnt < 0) {
        debounce_state[i].cnt = 0;
        debounce_state[i].state = S0; // Zustand: "losgelassen"
      }
    }
    // Fall 2: Taste ist GEDRÜCKT
    else {
      if (++debounce_state[i].cnt > CNTMAX) {
        debounce_state[i].cnt = CNTMAX;
        // Nur Event auslösen, wenn der Zustand vorher "losgelassen" war
        // (Flankenerkennung)
        if (debounce_state[i].state == S0) {
          debounce_state[i].state = S1;    // Zustand: "gedrückt"
          Event_set(button_config[i].msg); // entsprechendes Event setzen
          __low_power_mode_off_on_exit(); // CPU aufwecken, damit main reagieren
                                          // kann
        }
      }
    }
  }

  CLRBIT(TA1CTL, TAIFG); // Interrupt-Flag des Timers zurücksetzen
}
