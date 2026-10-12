#ifndef ALU_H
#define ALU_H
#include "types.h"
#include "mux.h"
#include  "adder.h"
#include "gates.h"

FourBitResult alu(FourBit a, FourBit b, FourBit s, int c_in);

#endif
