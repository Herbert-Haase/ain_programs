#include "..\base.h"
#include "TA0.h"
#include <msp430.h>

#define HIGH (0x8000)
#define LOW (0x0000)
#define REPEAT (0x4000) // Bit 14 als Flag für die Wiederholung
#define ACLKFRQ                                                                \
  (613750UL) // ACLK Frequenz als Unsigned Long für Integer-Arithmetik

// --- Integer-basiertes TICK-Makro ---
// (ACLKFRQ / div) wäre zu ungenau. Wir rechnen zuerst mit dem großen Wert.
// Um einen Überlauf bei ACLKFRQ * t zu vermeiden, stellen wir t in
// Millisekunden dar und teilen ACLKFRQ vorher durch 1000.
#define TICK(ms, div) ((UInt)((((ACLKFRQ / 1000) * (ms)) / (div)) - 1))

// === Definition der Musterdaten & Teiler ===
// Die Teiler werden pro Muster so gewählt, dass die längste *einzelne* Phase
// passt.

// Muster 1: max 2000ms. Faktor=(613750*2.0)/32768=37.45. Nächster Teiler:
// 40={/8}{/5}
static const Int muster1[] = {HIGH | TICK(2000, 40), LOW | TICK(500, 40), 0};

// Muster 2: max 750ms. Faktor=(613750*0.75)/32768=14.04. Nächster Teiler:
// 16={/8}{/2}
static const Int muster2[] = {HIGH | TICK(750, 16), LOW | TICK(750, 16), 0};

// Muster 3: max 250ms. Faktor=(613750*0.25)/32768=4.68. Nächster Teiler:
// 5={/1}{/5}
static const Int muster3[] = {HIGH | TICK(250, 5), LOW | TICK(250, 5), 0};

// Muster 4: max 1500ms. Faktor=(613750*1.5)/32768=28.09. Nächster Teiler:
// 32={/8}{/4}
static const Int muster4[] = {HIGH | TICK(500, 32), LOW | TICK(500, 32),
                              HIGH | TICK(1500, 32), 0};

// Muster 5: max 3500ms. Faktor=65.55. LÖSUNG: Phase aufteilen.
// Wir nehmen 1750ms (3500/2) und wiederholen sie.
// Faktor für 1750ms = (613750*1.75)/32768=32.77. Nächster Teiler: 35={/7}{/5}
static const Int muster5[] = {
    HIGH | TICK(500, 35),
    LOW | TICK(500, 35),
    HIGH | TICK(500, 35),
    LOW | TICK(500, 35),
    REPEAT | HIGH |
        TICK(1750, 35), // 1750ms, wird 1x wiederholt (ergibt 3500ms)
    0};

// Muster 6: max 4500ms. Faktor=84.28. LÖSUNG: Phase aufteilen.
// Wir nehmen 1500ms (4500/3) und wiederholen sie 2x.
// Faktor für 1500ms = 28.09. Nächster Teiler: 32={/8}{/4} (siehe Muster 4)
static const Int muster6[] = {
    HIGH | TICK(500, 32),
    LOW | TICK(500, 32),
    HIGH | TICK(500, 32),
    LOW | TICK(500, 32),
    HIGH | TICK(500, 32),
    LOW | TICK(500, 32),
    REPEAT | HIGH |
        TICK(1500, 32), // 1500ms, wird 2x wiederholt (ergibt 4500ms)
    0};

// --- Struktur zur Verwaltung der Muster (ohne float) ---
typedef struct {
  const Int *data;
  const UInt ctl_id;
  const UInt ex_taidex;
} BlinkPattern;

static const BlinkPattern all_patterns[] = {
    {muster1, ID__8, TAIDEX_4}, // Teiler 40
    {muster2, ID__8, TAIDEX_1}, // Teiler 16
    {muster3, ID__1, TAIDEX_4}, // Teiler 5
    {muster4, ID__8, TAIDEX_3}, // Teiler 32
    {muster5, ID__7, TAIDEX_4}, // Teiler 35
    {muster6, ID__8, TAIDEX_3}  // Teiler 32
};

// Globale Zustandsvariablen für die ISR
static const Int *ptr;
static UInt repeat_cnt = 0;
// Variable, die speichert, welches Muster aktiv ist, um es neustarten zu können
static MusterNum current_muster_num = MUSTER_1;

// --- Implementierung der Funktionen ---

GLOBAL Void set_blink_muster(MusterNum arg) {
  _disable_interrupt();
  current_muster_num = arg;
  const BlinkPattern *selected = &all_patterns[arg];
  ptr = selected->data;
  repeat_cnt = 0; // Wiederholungszähler zurücksetzen

  CLRBIT(TA0CTL, MC_3);
  TA0CTL = (TA0CTL & ~(ID_3)) | selected->ctl_id;
  TA0EX0 = selected->ex_taidex;

  SETBIT(TA0CTL, TACLR | TAIFG);
  _enable_interrupt();
}

#pragma FUNC_ALWAYS_INLINE(TA0_init)
GLOBAL Void TA0_init(Void) {
  TA0CTL = 0;
  TA0CCTL0 = 0;
  set_blink_muster(MUSTER_1); // Starte mit Muster 1
  TA0CTL |= TASSEL__ACLK | MC__UP | TAIE;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt Void TIMER0_A1_ISR(Void) {
  UInt cnt;

  if (repeat_cnt > 0) {
    repeat_cnt--;
    cnt = TA0CCR0;
  } else {
    if (*ptr == 0) { // Musterende erreicht
      // Starte das aktuell ausgewählte Muster neu
      ptr = all_patterns[current_muster_num].data;
    }

    cnt = *ptr;

    if (TSTBIT(cnt, REPEAT)) {
      CLRBIT(cnt, REPEAT);
      // Wie oft soll wiederholt werden? (hier fest im Code verankert)
      if (current_muster_num == MUSTER_5) {
        repeat_cnt = 1; // 1 Wiederholung -> 2 Durchläufe
      } else if (current_muster_num == MUSTER_6) {
        repeat_cnt = 2; // 2 Wiederholungen -> 3 Durchläufe
      }
    }
    ptr++;
  }

  if (TSTBIT(cnt, HIGH)) {
    SETBIT(P2OUT, BIT7);
    CLRBIT(cnt, HIGH);
  } else {
    CLRBIT(P2OUT, BIT7);
  }

  TA0CCR0 = cnt;
  CLRBIT(TA0CTL, TAIFG);
}
