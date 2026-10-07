#ifndef MUX_H
#define MUX_H
#include "types.h"

int OneBit11Mux(int a, int b, int s);
int OneBit41Mux(int a, int b, int c, int d, int s1, int s2);
FourBit FourBit41Mux(FourBit a, FourBit b, FourBit c, FourBit d, int s1, int s2);

#endif