#ifndef REGISTERS_H
#define REGISTERS_H
#include "types.h"
#include "mux.h"
#include "flipflop.h"

FourBitRegisterState InitFourBitRegister(FourBit initial);
FourBitRegisterState FourBitRegister(FourBitRegisterState state,FourBit D,int LOAD,int CLK);
CPURegisterBankState InitCPURegisterBank(FourBit initial);
CPURegisterBankState CPURegisterBank(CPURegisterBankState state, int loadA, int loadB, FourBit D, int CLK);

#endif