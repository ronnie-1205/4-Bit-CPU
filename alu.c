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
    
    result.Num.DO = A.D1;
    result.Num.D1 = A.D2;
    result.Num.D2 = A.D3;
    result.Num.D3 = c_in;
    result.carry = A.D0;

    return result;
}

FourBitResult ral(FourBit A, int c_in)
{
    FourBitResult result;
    
    result.Num.DO = c_in;
    result.Num.D1 = A.D0;
    result.Num.D2 = A.D1;
    result.Num.D3 = A.D2;
    result.carry = A.D3;

    return result;
}



FourBitResult alu(FourBit a, FourBit b, FourBit s, int c_in)
{
    FourBitResult result;
    FourBitResult ADD = FourBitAdder(a, b, c_in);
    FourBitResult SUB = FourBitSubtracter(a, b, c_in);
    FourBitResult IAC = FourBitAdder(a,{0,0,0,1},0);
    FourBitResult DAC = FourBitSubtracter(a,{0,0,0,1},0);

    FourBit CMA = cma(a);
    FourBitResult RAL = ral(a, c_in); 
    FourBitResult RAR = rar(a,c_in);

    FourBitResult CLB = {{0,0,0,0},0};
    FourBitResult CLC = {a,0};
    FourBitResult CMC = {a,NOT(c_in)};
    FourBitResult STC = {a,1};
    FourBitResult TCC = {{0,0,0,c_in},0};
    FourBitResult TCS = {{1,0,c_in,NOT(c_in)},0};

    

    return result;
}
