#include "adder.h"
#include "gates.h"

AdderResult HalfAdder(int a, int b)
{
    AdderResult HA_result;
    HA_result.sum = XOR(a,b);
    HA_result.carry =  AND(a,b);
    return HA_result;
}

AdderResult FullAdder(int a, int b, int c_in)
{
    AdderResult FA_result, HA1, HA2;
    
    HA1 = HalfAdder(a,b);
    HA2 = HalfAdder(HA1.sum, c_in);
    FA_result.sum = HA2.sum;
    FA_result.carry = OR(HA1.carry,HA2.carry);
    return FA_result;
}

FourBitResult FourBitAdder(FourBit a, FourBit b)
{
    FourBitResult FBA_Result;
    AdderResult FA0,FA1,FA2,FA3;
    
    FA0 = FullAdder(a.D0,b.D0,0);
    FA1 = FullAdder(a.D1, b.D1,FA0.carry);
    FA2 = FullAdder(a.D2, b.D2,FA1.carry);
    FA3 = FullAdder(a.D3, b.D3,FA2.carry);

    FBA_Result.sum.D0 = FA0.sum;
    FBA_Result.sum.D1 = FA1.sum;
    FBA_Result.sum.D2 = FA2.sum;
    FBA_Result.sum.D3 = FA3.sum;
    FBA_Result.carry = FA3.carry;
    
    return FBA_Result;
}

FourBit TwosComplement(FourBit a)
{
    FourBit TC_Result, FourBit1 = {1,0,0,0};
    
    TC_Result.D0 = !a.D0;
    TC_Result.D1 = !a.D1;
    TC_Result.D2 = !a.D2;
    TC_Result.D3 = !a.D3;

    TC_Result = FourBitAdder(TC_Result,FourBit1).sum;

    return TC_Result;
}

FourBitResult FourBitSubtracter(FourBit a, FourBit b)
{
    FourBitResult FBS_Result;
    
    FourBit temp = TwosComplement(b);

    FBS_Result = FourBitAdder(a,temp);

    return FBS_Result;
}