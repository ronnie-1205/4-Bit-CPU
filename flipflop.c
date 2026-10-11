#include "flipflop.h"

DFlipFlopState InitDFlipFlop(int initialQ)
{
    DFlipFlopState state;

    state.master = InitDLatch(initialQ);
    state.slave = InitDLatch(initialQ);
    state.Q = initialQ;

    return state;
}

DFlipFlopState DFlipFLop(DFlipFlopState state, int D,int CLK)
{
    state.master = Dlatch(state.master, D, NOT(CLK));
    state.slave = Dlatch(state.slave, state.master.Q, CLK);
    state.Q = state.slave.Q;
    
    return state;
}