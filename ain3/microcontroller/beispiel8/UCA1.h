#ifndef UCA1_H_
#define UCA1_H_

#include "..\base.h"

#define DRVWREN   (0x0008) // write enable
#define DRVRDEN   (0x0000) // read enable
#define DRVENABLE (0x0002) // display enable

// register address map
#define DRVDIG_0  (0x0000) // Digit 0 register
#define DRVDIG_1  (0x0001) // Digit 1 register
#define DRVDIG_2  (0x0002) // Digit 2 register
#define DRVDIG_3  (0x0003) // Digit 3 register
#define DRVCTL    (0x0004) // control register

EXTERN inline Void UCA1_init(Void);
EXTERN Int UCA1_emit(const UInt adr, const UInt val, const UInt msg);

// SPI4x7SEG Data Frame struct
// D15 D14 D13 D12 D11  D10  D9  D8   D7 D6 D5 D4 D3 D2 D1 D0
// X   X    X   X  R/W    Reg.-Adr.   MSB <--- Data ----> LSB
// -----------------------------------------------------------

// R/W = 0: Leseoperation
// R/W = 1: Schreiboperation

// Register Address Map
// Register       HEX Code              Reg-Adr
//                              D15:D12 D10 D9 D8
// Digit 0            0xX0         X     0   0  0
// Digit 1            0xX1         X     0   0  1
// Digit 2            0xX2         X     0   1  0
// Digit 3            0xX3         X     0   1  1
// Display Control    0xX4         X     1   0  0
//                    0xX5         X     1   0  1
//                    0xX6         X     1   1  0
//                    0xX7         X     1   1  1

// SCK ist Low im nicht aktiven Zustand
// Datenausgabe im SPI-Master erfolgt mit der steigender SCK-Flanke
// SEL ist High im nicht aktiven Zustand

#endif /* UCA1_H_ */
