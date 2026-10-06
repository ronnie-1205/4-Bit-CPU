#include "gates.h"

int XOR(int a, int b)
{
    return OR(AND(a,NOT(b)),AND(NOT(a),b));
}

int NAND(int a, int b)
{
    return NOT(AND(a,b));
}

int NOR(int a, int b)
{
    return NOT(OR(a,b));
}
