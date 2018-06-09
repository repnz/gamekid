#pragma once
#include "cpu/operand.h"
#include <memory>
class operands;
class cpu;
#include <GameKid/cpu_types.h>
#include <GameKid/memory.h>


class cpu
{
private:
    byte _sp_value_low;
    byte _sp_value_high;
    std::unique_ptr<operands> _operands;
public:
    reg8 A;
    reg8 B;
    reg8 C;
    reg8 D;
    reg8 E;
    flags_reg8 F;
    reg8 H;
    reg8 L;
    reg16 AF;
    reg16 BC;
    reg16 DE;
    reg16 HL;
    reg16 SP;
    word PC;
    bool _interrupts_enabled;

    operands& operands();
    void push(word value);
    word pop();
    void jump(word address);
    void enable_interrupts();

    memory mem;

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
    void inc(byte* val);
    void dec(byte* val);
    void swap(byte* val);
    static bool check_carry_up(word before, word after, byte bit_place);
    static bool check_carry_down(word before, word after, byte bit_place);
    ~cpu();
};