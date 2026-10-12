#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int sum;
    int carry;
} AdderResult;

typedef struct {
    int D3;
    int D2;
    int D1;
    int D0;
} FourBit;

typedef struct 
{
    FourBit Num;
    int carry;
} FourBitResult;

typedef struct {
    int D0;
    int D1;
} TwoBit;

typedef struct
{
    int Q;
    int Qbar;
} SRLatchState;

typedef struct 
{
    SRLatchState srlatch;
    int Q;
}DlatchState;

typedef struct
{
    DlatchState master;
    DlatchState slave;
    int Q;
} DFlipFlopState;

typedef struct
{
    DFlipFlopState bit0;
    DFlipFlopState bit1;
    DFlipFlopState bit2;
    DFlipFlopState bit3;

    FourBit Q;
} FourBitRegisterState;

typedef struct
{
    FourBitRegisterState registerA;
    FourBitRegisterState registerB;
} CPURegisterBankState;

typedef struct 
{
    FourBit I0;
    FourBit I1;
    FourBit I2;
    FourBit I3;
    FourBit I4;
    FourBit I5;
    FourBit I6;
    FourBit I7;
    FourBit I8;
    FourBit I9;
    FourBit I10;
    FourBit I11;
    FourBit I12;
    FourBit I13;
    FourBit I14;
    FourBit I15;
} Muxinput4Bit16_1;

typedef struct 
{
    int I0;
    int I1;
    int I2;
    int I3;
    int I4;
    int I5;
    int I6;
    int I7;
    int I8;
    int I9;
    int I10;
    int I11;
    int I12;
    int I13;
    int I14;
    int I15;
} Muxinput1Bit16_1;

#endif
