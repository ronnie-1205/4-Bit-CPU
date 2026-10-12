
#include "adder.h"
#include "gates.h"

AdderResult HalfAdder(int a, int b)
{
    AdderResult result;

    result.sum = XOR(a, b);
    result.carry = AND(a, b);

    return result;
}

AdderResult FullAdder(int a, int b, int c_in)
{
    AdderResult result, HA1, HA2;

    HA1 = HalfAdder(a, b);
    HA2 = HalfAdder(HA1.sum, c_in);

    result.sum = HA2.sum;
    result.carry = OR(HA1.carry, HA2.carry);

    return result;
}

FourBitResult FourBitAdder(FourBit a, FourBit b, int carry_in)
{
    FourBitResult result;
    AdderResult FA0, FA1, FA2, FA3;

    FA0 = FullAdder(a.D0, b.D0, carry_in);
    FA1 = FullAdder(a.D1, b.D1, FA0.carry);
    FA2 = FullAdder(a.D2, b.D2, FA1.carry);
    FA3 = FullAdder(a.D3, b.D3, FA2.carry);

    result.sum.D0 = FA0.sum;
    result.sum.D1 = FA1.sum;
    result.sum.D2 = FA2.sum;
    result.sum.D3 = FA3.sum;

    result.carry = FA3.carry;

    return result;
}

FourBitResult FourBitSubtracter(FourBit a, FourBit b, int borrow_in)
{
    FourBit inverted_b;

    inverted_b.D0 = NOT(b.D0);
    inverted_b.D1 = NOT(b.D1);
    inverted_b.D2 = NOT(b.D2);
    inverted_b.D3 = NOT(b.D3);

    return FourBitAdder(a, inverted_b, NOT(borrow_in));
}
