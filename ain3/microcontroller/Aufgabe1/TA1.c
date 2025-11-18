#include "TA1.h"
#include "..\base.h"
#include "event.h"
#include <msp430.h>

#define NUM_BUTTONS 2
#define CNTMAX 5

typedef enum { S0, S1 } TState;

// Zustandsspeicher fuer die Entprell-Logik jeder Taste
LOCAL struct {
  UChar cnt;
  TState state;
} debounce_state[NUM_BUTTONS];

// Konfiguration der Tasten-Hardware
LOCAL const struct {
  volatile UChar *const port;
  const UChar mask;
  const TEvent msg;
} button_config[NUM_BUTTONS] = {{(UChar *)(&P1IN), BIT0, EVENT_BTN1},
                                {(UChar *)(&P1IN), BIT1, EVENT_BTN2}};

// Index der naechsten zu pruefenden Taste
static UChar btn_statei;

#pragma FUNC_ALWAYS_INLINE(TA1_init)
GLOBAL Void TA1_init(Void) {
  TA1CTL = 0;   // stop mode
  TA1CCTL0 = 0; // compare mode

  btn_statei = 0;

    debounce_state[0].cnt = 0;
    debounce_state[0].state = S0;
    debounce_state[1].cnt = 0;
    debounce_state[1].state = S0;

  // Timer-Konfiguration fÃ¼r ca. 5ms Intervall
  TA1CCR0 = 1533;    // (613750Hz / 1) * 0.005s / 2 = 1534 - 1
  TA1EX0 = TAIDEX_0; // Teiler /1
  TA1CTL = TASSEL__ACLK | MC__UP | ID__1 | TACLR | TAIE;
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt Void TIMER1_A1_ISR(Void) {
  if (TA1IV == TA1IV_TAIFG) {
    // Fall 1: Taste ist NICHT gedrueckt (High-Pegel, da externe Pull-ups
    // angenommen)
    if (TSTBIT(*button_config[btn_statei].port,
               button_config[btn_statei].mask)) {
      if (debounce_state[btn_statei].cnt > 0) {
        debounce_state[btn_statei].cnt--;
      } else {
        debounce_state[btn_statei].state = S0; // Zustand "nicht gedrueckt"
      }
    }
    // Fall 2: Taste ist GEDRUECKT (Low-Pegel)
    else {
      if (debounce_state[btn_statei].cnt < CNTMAX) {
        debounce_state[btn_statei].cnt++;
      } else { // ZÃ¤hler am Maximum -> stabiler Zustand
        if (debounce_state[btn_statei].state == S0) {
          debounce_state[btn_statei].state = S1; // Zustand "gedrueckt" merken
          Event_set(button_config[btn_statei].msg);
          __low_power_mode_off_on_exit();
        }
      }
    }

    // Zur naechsten Taste fuer den naechsten ISR-Aufruf wechseln
    btn_statei++;
    if (btn_statei >= NUM_BUTTONS) {
      btn_statei = 0;
    }
  }
}

