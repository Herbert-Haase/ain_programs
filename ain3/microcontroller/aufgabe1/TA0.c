/*
 * TA0.c - Finale, bereinigte Version
 * Autor: Herbert-Haase
 * Datum: 2025-11-03
 *
 * Prinzip:
 * - Ein einziger, globaler Teiler wird für alle Muster verwendet.
 * - Der Teiler wird durch die längste Einzelphase im gesamten System
 *   bestimmt (2000 ms -> Faktor 37.45 -> Teiler 40).
 * - Die ISR ist maximal vereinfacht und enthält keine Sonderlogik.
 * - Die Umschaltung der Muster erfolgt durch reines Ändern eines Zeigers.
 */

#include "TA0.h"
#include "..\base.h"
#include <msp430.h>

#define HIGH (0x8000)
#define LOW (0x0000)
#define ACLKFRQ (613750UL)
#define GLOBAL_DIVIDER (40)
typedef Int MusterNum

// Makro, das den globalen Teiler für alle Tick-Berechnungen verwendet.
#define TICK(ms) ((UInt)((((ACLKFRQ / 1000) * (ms)) / GLOBAL_DIVIDER) - 1))

// === Definition der Musterdaten ===
// Alle Muster verwenden denselben Teiler von 40.
// Die längste Phase (2000ms) passt problemlos in 15 Bit: TICK(2000) = 30686 <
// 32768
//
// Zeitspanne = MAX (aller Muster) = 2000 ms
// Timer-Clock = 613.75 kHz
// Teilungsfaktor = Timer-Clock * Zeitspanne = 1227500
// 16 Bit-Timer: max. Schritte 2^15
// Skalierungsfaktor = 1227500 / 2^15 = 37.4603 => 40 = {/8} {/5}

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

// Globale Zustandsvariablen für die ISR
static const Int *ptr;
static MusterNum current_muster_num = MUSTER1;

// --- Implementierung der Funktionen ---

GLOBAL Void set_blink_muster(MusterNum arg) {
  _disable_interrupt();

  if (arg <= MUSTER6) {
    current_muster_num = arg;
    ptr = all_patterns[current_muster_num];
    SETBIT(TA0CTL, TAIFG);
  }

  _enable_interrupt();
}

#pragma FUNC_ALWAYS_INLINE(TA0_init)
GLOBAL Void TA0_init(Void) {
  TA0CTL = 0; // Timer stoppen für die Konfiguration
  TA0CCTL0 = 0;

  // Setze den globalen Teiler EINMALIG.
  TA0EX0 = TAIDEX_4;    // Expansion Divider /5
  TA0CTL = TASSEL__ACLK // Taktquelle
           | MC__UP     // Up Mode
           | ID__8      // Input Divider /8
           | TACLR      // Timer löschen
           | TAIE;      // Interrupts global aktivieren

  // Starte mit dem ersten Muster als Standard.
  set_blink_muster(MUSTER1);
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt Void TIMER0_A1_ISR(Void) {
  // Wenn das Muster-Ende (0) erreicht ist, starte das aktuelle Muster neu.
  if (*ptr == 0) {
    ptr = all_patterns[current_muster_num];
  }

  // Lade den aktuellen Schritt aus dem Muster-Array.
  UInt cnt = *ptr++;

  // Setze den LED-Zustand basierend auf dem HIGH-Bit.
  if (TSTBIT(cnt, HIGH)) {
    SETBIT(P2OUT, BIT7);
    CLRBIT(cnt, HIGH);
  } else {
    CLRBIT(P2OUT, BIT7);
  }

  // Lade den Timer mit dem neuen Wert und lösche das Interrupt-Flag.
  TA0CCR0 = cnt;
  CLRBIT(TA0CTL, TAIFG);
}
