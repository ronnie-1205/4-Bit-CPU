/*
 * Exhaustive/behavioral test harness for the 4-Bit-CPU project.
 * Run with: make test
 *
 * D0 is the least significant bit regardless of declaration order.
 * Tests deliberately compute expectations using normal C arithmetic;
 * the CPU implementation being tested still uses its own gate functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "gates.h"
#include "adder.h"
#include "mux.h"
#include "alu.h"
#include "latches.h"
#include "flipflop.h"
#include "clock.h"
#include "registers.h"

static unsigned long checks = 0;
static unsigned long failures = 0;
static unsigned long shown_failures = 0;

static void check(const char *group, const char *case_name, int actual, int expected)
{
    ++checks;
    if (actual != expected) {
        ++failures;
        if (shown_failures < 30) {
            fprintf(stderr, "FAIL [%-18s] %-36s got=%d expected=%d\n",
                    group, case_name, actual, expected);
            ++shown_failures;
        }
    }
}

static void group_report(const char *name, unsigned long start_checks, unsigned long start_failures)
{
    printf("%-22s %8lu checks   %s\n", name, checks - start_checks,
           failures == start_failures ? "PASS" : "FAIL");
}

static FourBit four(unsigned value)
{
    FourBit bits = {
        .D3 = (int)((value >> 3) & 1u),
        .D2 = (int)((value >> 2) & 1u),
        .D1 = (int)((value >> 1) & 1u),
        .D0 = (int)(value & 1u)
    };
    return bits;
}

static int number(FourBit bits)
{
    return (bits.D3 << 3) | (bits.D2 << 2) | (bits.D1 << 1) | bits.D0;
}

static void test_gates(void)
{
    unsigned long start = checks, failed = failures;
    char label[80];
    for (int a = 0; a < 2; ++a) {
        snprintf(label, sizeof label, "NOT(%d)", a);
        check("gates", label, NOT(a), !a);
        for (int b = 0; b < 2; ++b) {
            snprintf(label, sizeof label, "AND(%d,%d)", a, b);
            check("gates", label, AND(a, b), a & b);
            snprintf(label, sizeof label, "OR(%d,%d)", a, b);
            check("gates", label, OR(a, b), a | b);
            snprintf(label, sizeof label, "XOR(%d,%d)", a, b);
            check("gates", label, XOR(a, b), a ^ b);
            snprintf(label, sizeof label, "NAND(%d,%d)", a, b);
            check("gates", label, NAND(a, b), !(a & b));
            snprintf(label, sizeof label, "NOR(%d,%d)", a, b);
            check("gates", label, NOR(a, b), !(a | b));
        }
    }
    group_report("Logic gates", start, failed);
}

static void test_adders(void)
{
    unsigned long start = checks, failed = failures;
    char label[96];
    for (int a = 0; a < 2; ++a)
        for (int b = 0; b < 2; ++b) {
            AdderResult r = HalfAdder(a, b);
            snprintf(label, sizeof label, "half(%d,%d) sum", a, b);
            check("adders", label, r.sum, a ^ b);
            snprintf(label, sizeof label, "half(%d,%d) carry", a, b);
            check("adders", label, r.carry, a & b);
            for (int ci = 0; ci < 2; ++ci) {
                r = FullAdder(a, b, ci);
                snprintf(label, sizeof label, "full(%d,%d,%d) sum", a, b, ci);
                check("adders", label, r.sum, (a + b + ci) & 1);
                snprintf(label, sizeof label, "full(%d,%d,%d) carry", a, b, ci);
                check("adders", label, r.carry, (a + b + ci) >> 1);
            }
        }
    for (int a = 0; a < 16; ++a)
        for (int b = 0; b < 16; ++b)
            for (int ci = 0; ci < 2; ++ci) {
                FourBitResult add = FourBitAdder(four((unsigned)a), four((unsigned)b), ci);
                FourBitResult sub = FourBitSubtracter(four((unsigned)a), four((unsigned)b), ci);
                int total = a + b + ci;
                int diff = a - b - ci;
                snprintf(label, sizeof label, "ADD a=%X b=%X ci=%d value", a, b, ci);
                check("adders", label, number(add.Num), total & 15);
                snprintf(label, sizeof label, "ADD a=%X b=%X ci=%d carry", a, b, ci);
                check("adders", label, add.carry, total > 15);
                snprintf(label, sizeof label, "SUB a=%X b=%X borrow=%d value", a, b, ci);
                check("adders", label, number(sub.Num), diff & 15);
                snprintf(label, sizeof label, "SUB a=%X b=%X borrow=%d carry", a, b, ci);
                check("adders", label, sub.carry, diff >= 0);
            }
    group_report("Half/full/4-bit arithmetic", start, failed);
}

static Muxinput1Bit16_1 input16_one(unsigned mask)
{
    Muxinput1Bit16_1 in = {
        .I0 = (int)((mask >> 0) & 1u), .I1 = (int)((mask >> 1) & 1u),
        .I2 = (int)((mask >> 2) & 1u), .I3 = (int)((mask >> 3) & 1u),
        .I4 = (int)((mask >> 4) & 1u), .I5 = (int)((mask >> 5) & 1u),
        .I6 = (int)((mask >> 6) & 1u), .I7 = (int)((mask >> 7) & 1u),
        .I8 = (int)((mask >> 8) & 1u), .I9 = (int)((mask >> 9) & 1u),
        .I10 = (int)((mask >> 10) & 1u), .I11 = (int)((mask >> 11) & 1u),
        .I12 = (int)((mask >> 12) & 1u), .I13 = (int)((mask >> 13) & 1u),
        .I14 = (int)((mask >> 14) & 1u), .I15 = (int)((mask >> 15) & 1u)
    };
    return in;
}

static Muxinput4Bit16_1 input16_four(unsigned shift)
{
    Muxinput4Bit16_1 in = {
        .I0 = four((0u + shift) & 15u), .I1 = four((1u + shift) & 15u),
        .I2 = four((2u + shift) & 15u), .I3 = four((3u + shift) & 15u),
        .I4 = four((4u + shift) & 15u), .I5 = four((5u + shift) & 15u),
        .I6 = four((6u + shift) & 15u), .I7 = four((7u + shift) & 15u),
        .I8 = four((8u + shift) & 15u), .I9 = four((9u + shift) & 15u),
        .I10 = four((10u + shift) & 15u), .I11 = four((11u + shift) & 15u),
        .I12 = four((12u + shift) & 15u), .I13 = four((13u + shift) & 15u),
        .I14 = four((14u + shift) & 15u), .I15 = four((15u + shift) & 15u)
    };
    return in;
}

static void test_muxes(void)
{
    unsigned long start = checks, failed = failures;
    char label[96];
    for (int pattern = 0; pattern < 4; ++pattern)
        for (int select = 0; select < 2; ++select) {
            int a = pattern & 1, b = (pattern >> 1) & 1;
            snprintf(label, sizeof label, "1-bit 2:1 pat=%d select=%d", pattern, select);
            check("mux", label, OneBit21Mux(a, b, select), select ? b : a);
        }
    for (int pattern = 0; pattern < 16; ++pattern)
        for (int select = 0; select < 4; ++select) {
            int got = OneBit41Mux(pattern & 1, (pattern >> 1) & 1,
                                  (pattern >> 2) & 1, (pattern >> 3) & 1,
                                  select & 1, (select >> 1) & 1);
            snprintf(label, sizeof label, "1-bit 4:1 pat=%X select=%d", pattern, select);
            check("mux", label, got, (pattern >> select) & 1);
        }
    for (int select = 0; select < 4; ++select) {
        FourBit got = FourBit41Mux(four(1), four(5), four(10), four(15),
                                   select & 1, (select >> 1) & 1);
        const int expected[4] = {1, 5, 10, 15};
        snprintf(label, sizeof label, "4-bit 4:1 select=%d", select);
        check("mux", label, number(got), expected[select]);
    }
    for (int active = 0; active < 16; ++active) {
        Muxinput1Bit16_1 in = input16_one(1u << active);
        for (int select = 0; select < 16; ++select) {
            snprintf(label, sizeof label, "1-bit 16:1 active=%d sel=%d", active, select);
            check("mux", label, OneBit161Mux(in, four((unsigned)select)), active == select);
        }
    }
    for (unsigned shift = 0; shift < 16; ++shift) {
        Muxinput4Bit16_1 in = input16_four(shift);
        for (int select = 0; select < 16; ++select) {
            snprintf(label, sizeof label, "4-bit 16:1 shift=%u sel=%d", shift, select);
            check("mux", label, number(FourBit161Mux(in, four((unsigned)select))),
                  (int)((shift + (unsigned)select) & 15u));
        }
    }
    group_report("Multiplexers", start, failed);
}

static int expected_kbp(int a)
{
    switch (a) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 4: return 3;
        case 8: return 4;
        default: return 15;
    }
}

/* Software oracle only; this is NOT used to implement the ALU. */
static void expected_alu(int select, int a, int b, int cy, int *value, int *carry)
{
    int n = a, c = cy, tmp;
    switch (select) {
        case 0: break;                                    /* PASS A */
        case 1: tmp = a + b + cy; n = tmp & 15; c = tmp > 15; break;
        case 2: tmp = a - b - cy; n = tmp & 15; c = tmp >= 0; break;
        case 3: tmp = a + 1; n = tmp & 15; c = tmp > 15; break;
        case 4: tmp = a - 1; n = tmp & 15; c = tmp >= 0; break;
        case 5: n = (~a) & 15; break;
        case 6: n = ((a << 1) | cy) & 15; c = (a >> 3) & 1; break;
        case 7: n = (a >> 1) | (cy << 3); c = a & 1; break;
        case 8: n = 0; c = 0; break;
        case 9: c = 0; break;
        case 10: c = !cy; break;
        case 11: c = 1; break;
        case 12: n = cy; c = 0; break;
        case 13: n = cy ? 10 : 9; c = 0; break;
        case 14:
            tmp = a + ((a > 9 || cy) ? 6 : 0);
            n = tmp & 15;
            c = cy || tmp > 15;
            break;
        case 15: n = expected_kbp(a); break;
        default: abort();
    }
    *value = n;
    *carry = c;
}

static void test_alu(void)
{
    static const char *names[16] = {
        "PASS", "ADD", "SUB", "IAC", "DAC", "CMA", "RAL", "RAR",
        "CLB", "CLC", "CMC", "STC", "TCC", "TCS", "DAA", "KBP"
    };
    unsigned long start = checks, failed = failures;
    char label[96];
    for (int op = 0; op < 16; ++op)
        for (int a = 0; a < 16; ++a)
            for (int b = 0; b < 16; ++b)
                for (int cy = 0; cy < 2; ++cy) {
                    int value, carry;
                    FourBitResult got = alu(four((unsigned)a), four((unsigned)b),
                                            four((unsigned)op), cy);
                    expected_alu(op, a, b, cy, &value, &carry);
                    snprintf(label, sizeof label, "%s A=%X B=%X CY=%d result", names[op], a, b, cy);
                    check("ALU", label, number(got.Num), value);
                    snprintf(label, sizeof label, "%s A=%X B=%X CY=%d carry", names[op], a, b, cy);
                    check("ALU", label, got.carry, carry);
                }
    group_report("ALU: all 16 operations", start, failed);
}

static void test_latches(void)
{
    unsigned long start = checks, failed = failures;
    SRLatchState sr = InitSRLatch(0);
    check("SR latch", "initial Q", sr.Q, 0);
    check("SR latch", "initial Qbar", sr.Qbar, 1);
    sr = SRLatch(sr, 1, 0);
    check("SR latch", "set Q", sr.Q, 1);
    check("SR latch", "set Qbar", sr.Qbar, 0);
    sr = SRLatch(sr, 0, 0);
    check("SR latch", "hold Q", sr.Q, 1);
    sr = SRLatch(sr, 0, 1);
    check("SR latch", "reset Q", sr.Q, 0);
    check("SR latch", "reset Qbar", sr.Qbar, 1);
    /* Your SR latch models the forbidden S=R=1 case as Q=Qbar=0. */
    sr = SRLatch(sr, 1, 1);
    check("SR latch", "forbidden state Q (model)", sr.Q, 0);
    check("SR latch", "forbidden state Qbar (model)", sr.Qbar, 0);

    DlatchState dl = InitDLatch(0);
    dl = Dlatch(dl, 1, 0);
    check("D latch", "disabled holds zero", dl.Q, 0);
    dl = Dlatch(dl, 1, 1);
    check("D latch", "enabled tracks one", dl.Q, 1);
    dl = Dlatch(dl, 0, 0);
    check("D latch", "disabled holds one", dl.Q, 1);
    dl = Dlatch(dl, 0, 1);
    check("D latch", "enabled tracks zero", dl.Q, 0);
    group_report("SR and D latches", start, failed);
}

static void test_flipflop(void)
{
    unsigned long start = checks, failed = failures;
    DFlipFlopState ff = InitDFlipFlop(0);
    check("flip-flop", "initial Q", ff.Q, 0);
    ff = DFlipFLop(ff, 1, 0);
    check("flip-flop", "low clock, master captures only", ff.Q, 0);
    ff = DFlipFLop(ff, 1, 1);
    check("flip-flop", "rising edge captures one", ff.Q, 1);
    ff = DFlipFLop(ff, 0, 1);
    check("flip-flop", "high clock cannot recapture", ff.Q, 1);
    ff = DFlipFLop(ff, 0, 0);
    check("flip-flop", "falling edge holds one", ff.Q, 1);
    ff = DFlipFLop(ff, 0, 1);
    check("flip-flop", "next rising captures zero", ff.Q, 0);
    DFlipFlopState initially_one = InitDFlipFlop(1);
    check("flip-flop", "initialization to one", initially_one.Q, 1);
    group_report("D flip-flop", start, failed);
}

static void test_clock(void)
{
    unsigned long start = checks, failed = failures;
    int clk = 0;
    for (int step = 0; step < 10; ++step) {
        clk = TickClock(clk);
        check("clock", "clock toggles", clk, (step + 1) & 1);
    }
    group_report("Clock toggle", start, failed);
}

static void test_register(void)
{
    unsigned long start = checks, failed = failures;
    FourBitRegisterState reg = InitFourBitRegister(four(3));
    check("register", "initial value", number(reg.Q), 3);
    reg = FourBitRegister(reg, four(10), 1, 0);
    check("register", "no change before rising edge", number(reg.Q), 3);
    reg = FourBitRegister(reg, four(10), 1, 1);
    check("register", "load on rising edge", number(reg.Q), 10);
    reg = FourBitRegister(reg, four(7), 1, 1);
    check("register", "ignores changed input while high", number(reg.Q), 10);
    reg = FourBitRegister(reg, four(7), 0, 0);
    reg = FourBitRegister(reg, four(7), 0, 1);
    check("register", "LOAD=0 holds value", number(reg.Q), 10);
    reg = FourBitRegister(reg, four(7), 1, 0);
    reg = FourBitRegister(reg, four(7), 1, 1);
    check("register", "next enabled rising edge", number(reg.Q), 7);
    group_report("4-bit register", start, failed);
}

static void test_register_bank(void)
{
    unsigned long start = checks, failed = failures;
    CPURegisterBankState bank = InitCPURegisterBank(four(1));
    check("bank", "initial A", number(bank.registerA.Q), 1);
    check("bank", "initial B", number(bank.registerB.Q), 1);

    bank = CPURegisterBank(bank, 1, 0, four(5), 0);
    bank = CPURegisterBank(bank, 1, 0, four(5), 1);
    check("bank", "load A only: A", number(bank.registerA.Q), 5);
    check("bank", "load A only: B", number(bank.registerB.Q), 1);

    bank = CPURegisterBank(bank, 0, 1, four(10), 0);
    bank = CPURegisterBank(bank, 0, 1, four(10), 1);
    check("bank", "load B only: A", number(bank.registerA.Q), 5);
    check("bank", "load B only: B", number(bank.registerB.Q), 10);

    bank = CPURegisterBank(bank, 1, 1, four(15), 0);
    bank = CPURegisterBank(bank, 1, 1, four(15), 1);
    check("bank", "load both: A", number(bank.registerA.Q), 15);
    check("bank", "load both: B", number(bank.registerB.Q), 15);

    bank = CPURegisterBank(bank, 0, 0, four(0), 0);
    bank = CPURegisterBank(bank, 0, 0, four(0), 1);
    check("bank", "hold both: A", number(bank.registerA.Q), 15);
    check("bank", "hold both: B", number(bank.registerB.Q), 15);
    group_report("Two-register bank", start, failed);
}

int main(void)
{
    puts("4-Bit-CPU component test suite");
    puts("===============================================");
    test_gates();
    test_adders();
    test_muxes();
    test_alu();
    test_latches();
    test_flipflop();
    test_clock();
    test_register();
    test_register_bank();
    puts("===============================================");
    printf("Total: %lu checks, %lu failures\n", checks, failures);
    if (failures > shown_failures)
        printf("(Only the first %lu failures were printed.)\n", shown_failures);
    puts(failures == 0 ? "ALL TESTS PASSED" : "TESTS FAILED");
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
