#ifndef flipflop_H
#define flipflop_H

#include "types.h"
#include "latches.h"

DFlipFlopState InitDFlipFlop(int initialQ);
DFlipFlopState DFlipFLop(DFlipFlopState state, int D,int CLK);

#endif