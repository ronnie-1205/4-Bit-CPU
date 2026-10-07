#ifndef ALU_H
#define ALU_H
#include "types.h"
#include "mux.h"
#include "adder.h"
#include "gates.h"

AluResult alu(FourBit a, FourBit b, TwoBit s);

#endif
