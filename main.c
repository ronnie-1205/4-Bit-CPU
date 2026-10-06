#include<stdio.h>
#include "gates.h"
#include "adder.h"

int main()
{
    FourBit a,b;
    FourBitResult ans;
    printf("Num1: ");
    scanf(" %d %d %d %d", &a.D3,&a.D2,&a.D1,&a.D0);
    printf("Num2: ");
    scanf(" %d %d %d %d", &b.D3,&b.D2,&b.D1,&b.D0);
    ans = FourBitSubtracter(a,b);
    printf("sum: %d%d%d%d \n carry: %d", ans.sum.D3,ans.sum.D2,ans.sum.D1,ans.sum.D0, ans.carry);

}