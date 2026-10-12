
#ifndef ADDER_H
#define ADDER_H

#include "types.h"

AdderResult HalfAdder(int a, int b);
AdderResult FullAdder(int a, int b, int c_in);

FourBitResult FourBitAdder(FourBit a, FourBit b, int carry_in);
FourBitResult FourBitSubtracter(FourBit a, FourBit b, int borrow_in);

#endif
