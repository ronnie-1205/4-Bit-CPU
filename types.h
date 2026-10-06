#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int sum;
    int carry;
} AdderResult;

typedef struct {
    int D0;
    int D1;
    int D2;
    int D3;
} FourBit;

typedef struct 
{
    FourBit sum;
    int carry;
} FourBitResult;

typedef struct {
    FourBit result;
    int carry;
    int zero;
} AluResult;

typedef struct {
    int D0;
    int D1;
} TwoBit;

#endif
