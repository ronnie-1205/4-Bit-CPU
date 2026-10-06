#include "alu.h"

FourBit FourBitAND(FourBit a, FourBit b)
{
    FourBit result;
    result.D0 = AND(a.D0, b.D0);
    result.D1 = AND(a.D1, b.D1);
    result.D2 = AND(a.D2, b.D2);
    result.D3 = AND(a.D3, b.D3);

    return result;
}

FourBit FourBitOR(FourBit a, FourBit b)
{
    FourBit result;
    result.D0 = OR(a.D0, b.D0);
    result.D1 = OR(a.D1, b.D1);
    result.D2 = OR(a.D2, b.D2);
    result.D3 = OR(a.D3, b.D3);

    return result;
}

AluResult alu(FourBit a, FourBit b, TwoBit s)
{
    AluResult result;
    FourBitResult add = FourBitAdder(a,b);
    FourBitResult sub = FourBitSubtracter(a,b);
    FourBit and = FourBitAND(a,b);
    FourBit or = FourBitOR(a,b);

    result.result = FourBit41Mux(add.sum,sub.sum,and,or,s.D0,s.D1);
    result.carry = OneBit41Mux(add.carry, sub.carry,0,0,s.D0,s.D1);
    result.zero = NOT(OR(OR(result.result.D0,result.result.D1),OR(result.result.D2,result.result.D3))); 
    return result;
}