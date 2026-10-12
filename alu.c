#include "alu.h"

FourBit cma(FourBit A)
{
    FourBit result;
    result.D0 = NOT(A.D0);
    result.D1 = NOT(A.D1);
    result.D2 = NOT(A.D2);
    result.D3 = NOT(A.D3);

    return result;
}

FourBitResult rar(FourBit A, int c_in)
{
    FourBitResult result;
    
    result.Num.D0 = A.D1;
    result.Num.D1 = A.D2;
    result.Num.D2 = A.D3;
    result.Num.D3 = c_in;
    result.carry = A.D0;

    return result;
}

FourBitResult ral(FourBit A, int c_in)
{
    FourBitResult result;
    
    result.Num.D0 = c_in;
    result.Num.D1 = A.D0;
    result.Num.D2 = A.D1;
    result.Num.D3 = A.D2;
    result.carry = A.D3;

    return result;
}


FourBitResult daa(FourBit a, int c_in)
{
    int G = AND(a.D3, OR(a.D2, a.D1));
    int adjust = OR(G, c_in);

    FourBit correction = {
        .D3 = 0,
        .D2 = adjust,
        .D1 = adjust,
        .D0 = 0
    };

    FourBitResult result = FourBitAdder(a, correction, 0);

    result.carry = OR(c_in, result.carry);

    return result;
}


FourBitResult kbp(FourBit a, int c_in)
{
    int zero = AND(
        AND(NOT(a.D3), NOT(a.D2)),
        AND(NOT(a.D1), NOT(a.D0))
    );

    int key1 = AND(a.D0,
        AND(NOT(a.D1),
        AND(NOT(a.D2), NOT(a.D3))));

    int key2 = AND(a.D1,
        AND(NOT(a.D0),
        AND(NOT(a.D2), NOT(a.D3))));

    int key3 = AND(a.D2,
        AND(NOT(a.D0),
        AND(NOT(a.D1), NOT(a.D3))));

    int key4 = AND(a.D3,
        AND(NOT(a.D0),
        AND(NOT(a.D1), NOT(a.D2))));

    int valid = OR(
        OR(zero, key1),
        OR(key2, OR(key3, key4))
    );

    int invalid = NOT(valid);

    FourBitResult result;

    result.Num.D0 = OR(invalid, OR(key1, key3));
    result.Num.D1 = OR(invalid, OR(key2, key3));
    result.Num.D2 = OR(invalid, key4);
    result.Num.D3 = invalid;

    result.carry = c_in;

    return result;
}

FourBitResult alu(FourBit a, FourBit b, FourBit s, int c_in)
{
    FourBitResult result;
    FourBitResult ADD = FourBitAdder(a, b, c_in);
    FourBitResult SUB = FourBitSubtracter(a, b, c_in);
    FourBitResult IAC = FourBitAdder(a,(FourBit){0,0,0,1},0);
    FourBitResult DAC = FourBitSubtracter(a,(FourBit){0,0,0,1},0);

    FourBit CMA = cma(a);
    FourBitResult RAL = ral(a, c_in); 
    FourBitResult RAR = rar(a,c_in);

    FourBitResult CLB = {{0,0,0,0},0};
    FourBitResult CLC = {a,0};
    FourBitResult CMC = {a,NOT(c_in)};
    FourBitResult STC = {a,1};
    FourBitResult TCC = {{0,0,0,c_in},0};
    FourBitResult TCS = {{1,0,c_in,NOT(c_in)},0};

    FourBitResult DAA = daa(a, c_in);
    FourBitResult KBP = kbp(a,c_in);

    Muxinput4Bit16_1 NumInput = {a,ADD.Num,SUB.Num,IAC.Num,DAC.Num,CMA,RAL.Num,RAR.Num,CLB.Num,CLC.Num,CMC.Num,STC.Num,TCC.Num,TCS.Num,DAA.Num,KBP.Num,};
    Muxinput1Bit16_1 CarryInput = {c_in,ADD.carry,SUB.carry,IAC.carry,DAC.carry,c_in,RAL.carry,RAR.carry,CLB.carry,CLC.carry,CMC.carry,STC.carry,TCC.carry,TCS.carry,DAA.carry,KBP.carry};

    result.Num = FourBit161Mux(NumInput,s);
    result.carry = OneBit161Mux(CarryInput, s);

    return result;
}
