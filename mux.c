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

FourBit FourBit41Mux(FourBit a, FourBit b, FourBit c, FourBit d, int s1, int s2)
{
    FourBit result;

    result.D0 = OneBit41Mux(a.D0, b.D0, c.D0, d.D0, s1, s2);
    result.D1 = OneBit41Mux(a.D1, b.D1, c.D1, d.D1, s1, s2);
    result.D2 = OneBit41Mux(a.D2, b.D2, c.D2, d.D2, s1, s2);
    result.D3 = OneBit41Mux(a.D3, b.D3, c.D3, d.D3, s1, s2);

    return result;
}
