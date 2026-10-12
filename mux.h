#ifndef MUX_H
#define MUX_H
#include "types.h"

int OneBit21Mux(int a, int b, int s);
int OneBit41Mux(int a, int b, int c, int d, int s1, int s2);
int OneBit161Mux(Muxinput1Bit16_1 input, FourBit s);
FourBit FourBit41Mux(FourBit a, FourBit b, FourBit c, FourBit d, int s1, int s2);
FourBit FourBit161Mux(Muxinput4Bit16_1 input, FourBit s);

#endif