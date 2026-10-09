#ifndef LATCHES_H
#define LATCHES_H
#include "types.h"
#include "gates.h" 

SRLatchState InitSRLatch(int initialQ);
SRLatchState SRLatch(SRLatchState state, int S, int R);
DlatchState InitDLatch(int initialQ);
DlatchState Dlatch(DlatchState state, int D, int E);

#endif