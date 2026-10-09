#include "latches.h"

SRLatchState InitSRLatch(int initialQ)
{
    SRLatchState state;

    state.Q = initialQ;
    state.Qbar = !initialQ;

    return state;
}


SRLatchState SRLatch(SRLatchState state, int S, int R)
{
    if (S == 0 && R == 0)
    {
        return state;
    }

    if (S == 1 && R == 0)
    {
        state.Q = 1;
        state.Qbar = 0;
        return state;
    }

    if (S == 0 && R == 1)
    {
        state.Q = 0;
        state.Qbar = 1;
        return state;
    }

    state.Q = 0;
    state.Qbar = 0;

    return state;
}

DlatchState InitDLatch(int initialQ)
{
    DlatchState state;

    state.srlatch = InitSRLatch(initialQ);
    state.Q = initialQ;

    return state;
}

DlatchState Dlatch(DlatchState state, int D, int E)
{
    state.srlatch = SRLatch(state.srlatch, AND(D,E), AND(NOT(D), E));
    state.Q = state.srlatch.Q;
    return state;
}
