#pragma once
#include <string>
class cpu;
#include <GameKid/cpu_types.h>
#include <GameKid/memory.h>

struct reg8
{
    std::string name;
    byte* address;

    reg8(const std::string& name, byte* address) : name(name), address(address) {}

};

struct reg16
{
    std::string name;
    byte* high;
    byte* low;

    reg16(const std::string& name, byte* high, byte* low) : name(name), high(high), low(low){}

    void set(word w)
    {
        *low = w & 0xff;
        *high = w >> 8;
    }

    word get()
    {
        return (*high << 8) + *low;
    }
};

struct regs
{
    reg8 A;
    reg8 B;
    reg8 C;
    reg8 D;
    reg8 E;
    reg8 H;
    reg8 L;
    reg16 BC;
    reg16 DE;
    reg16 HL;
    explicit regs(cpu& cpu);
};

class cpu
{
private:
    byte _A;
    byte _B;
    byte _C;
    byte _D;
    byte _E;
    byte _H;
    byte _L;
public:
    word SP;
    word PC;
    byte zero_flag;
    byte substruct_flag;
    byte half_carry_flag;
    byte carry_flag;

    memory mem;
    regs regs;

    cpu();

    void next();

    void halt();
    void stop();
    void error();
    void rla();
    void rlca();
    void ccf();
    void scf();
    void rrca();
    void rra();
    void bit(byte val, byte bitPlace);
    void rl(byte* val);
    void rlc(byte* val);
    void rrc(byte* val);
    void rr(byte* val);
    void sla(byte* val);
    void sra(byte* val);
    void srl(byte* val);
    void run();
    void set(byte* val, byte bit_place);
    void res(byte* val, byte bit_place);
    void add(byte* val, byte n, bool carry = false);
    void adc(byte* val, byte n);
    void sub(byte* val, byte n, bool carry = false, bool save_result = true);
    void sbc(byte* val, byte n);
    void and_n(byte* val, byte n);
    void or_n(byte* val, byte n);
    void xor_n(byte* a, byte byte);
    void cp(byte val, byte byte);
    void set_zero_flag(byte val);
    void inc(byte* val);
    void dec(byte* val);
    void swap(byte* val);
    void ld(byte* val);
    void ld(byte* r1, byte r2);

    friend struct regs;
};


inline regs::regs(cpu& cpu) :
        A("A", &cpu._A),
        B("B", &cpu._B),
        C("C", &cpu._C),
        D("D", &cpu._D),
        E("E", &cpu._E),
        H("H", &cpu._H),
        L("L", &cpu._L),
        BC("BC", &cpu._B, &cpu._C),
        DE("DE", &cpu._D, &cpu._D),
        HL("HL", &cpu._H, &cpu._L)
{
}
