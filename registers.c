#include "registers.h"


FourBitRegisterState InitFourBitRegister(FourBit initial)
{
    FourBitRegisterState state;

    state.bit0 = InitDFlipFlop(initial.D0);
    state.bit1 = InitDFlipFlop(initial.D1);
    state.bit2 = InitDFlipFlop(initial.D2);
    state.bit3 = InitDFlipFlop(initial.D3);

    state.Q = initial;

    return state;
}

FourBitRegisterState FourBitRegister(FourBitRegisterState state,FourBit D,int LOAD,int CLK)
{
    int d0 = OneBit21Mux(state.Q.D0, D.D0, LOAD);
    int d1 = OneBit21Mux(state.Q.D1, D.D1, LOAD);
    int d2 = OneBit21Mux(state.Q.D2, D.D2, LOAD);
    int d3 = OneBit21Mux(state.Q.D3, D.D3, LOAD);

    state.bit0 = DFlipFLop(state.bit0, d0, CLK);
    state.bit1 = DFlipFLop(state.bit1, d1, CLK);
    state.bit2 = DFlipFLop(state.bit2, d2, CLK);
    state.bit3 = DFlipFLop(state.bit3, d3, CLK);

    state.Q.D0 = state.bit0.Q;
    state.Q.D1 = state.bit1.Q;
    state.Q.D2 = state.bit2.Q;
    state.Q.D3 = state.bit3.Q;

    return state;
}

CPURegisterBankState InitCPURegisterBank(FourBit initial)
{
    CPURegisterBankState state;

    state.registerA = InitFourBitRegister(initial);
    state.registerB = InitFourBitRegister(initial);

    return state;
}

CPURegisterBankState CPURegisterBank(CPURegisterBankState state, int loadA, int loadB, FourBit D, int CLK)
{
    state.registerA = FourBitRegister(state.registerA, D, loadA, CLK);
    state.registerB = FourBitRegister(state.registerB, D, loadB, CLK);

    return state;
}