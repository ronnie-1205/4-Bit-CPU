#include "gates.h"
#include "mux.h"

int OneBit21Mux(int a, int b, int s)
{
    return OR(AND(a,NOT(s)),AND(b,s));
}

int OneBit41Mux(int a, int b, int c, int d, int s1, int s2)
{
    int A,B,result;

    A = OneBit21Mux(a,b,s1);
    B = OneBit21Mux(c,d,s1);

    result = OneBit21Mux(A,B,s2);
    return result;
}

int OneBit161Mux(Muxinput1Bit16_1 input, FourBit s)
{
    int A,B,C,D,result;

    A = OneBit41Mux(input.I0, input.I1, input.I2, input.I3, s.D0, s.D1);
    B = OneBit41Mux(input.I4, input.I5, input.I6, input.I7, s.D0, s.D1);
    C = OneBit41Mux(input.I8, input.I9, input.I10, input.I11, s.D0, s.D1);
    D = OneBit41Mux(input.I12, input.I13, input.I14, input.I15, s.D0, s.D1);

    result = OneBit41Mux(A,B,C,D,s.D2,s.D3);
    return result;
}

FourBit FourBit41Mux(FourBit a, FourBit b, FourBit c, FourBit d, int s1, int s2)
{
    FourBit result;

    result.D0 = OneBit41Mux(a.D0, b.D0, c.D0, d.D0, s1, s2);
    result.D1 = OneBit41Mux(a.D1, b.D1, c.D1, d.D1, s1, s2);
    result.D2 = OneBit41Mux(a.D2, b.D2, c.D2, d.D2, s1, s2);
    result.D3 = OneBit41Mux(a.D3, b.D3, c.D3, d.D3, s1, s2);

    return result;
}


FourBit FourBit161Mux(Muxinput4Bit16_1 input, FourBit s)
{
    FourBit A,B,C,D,result;

    A = FourBit41Mux(input.I0, input.I1, input.I2, input.I3, s.D0, s.D1);
    B = FourBit41Mux(input.I4, input.I5, input.I6, input.I7, s.D0, s.D1);
    C = FourBit41Mux(input.I8, input.I9, input.I10, input.I11, s.D0, s.D1);
    D = FourBit41Mux(input.I12, input.I13, input.I14, input.I15, s.D0, s.D1);

    result = OneBit41Mux(A,B,C,D,s.D2,s.D3);
    return result;
}

