#ifndef GATES_H
#define GATES_H

#define AND(a,b) ((a) && (b))
#define OR(a,b) ((a) || (b))
#define NOT(a) (!a)

int XOR(int a, int b);
int NAND(int a, int b);
int NOR(int a, int b);

#endif