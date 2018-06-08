#include <GameKid/cpu.h>
#include "cpu/operands.h"


operands& cpu::operands()
{
    return *_operands.get();
}

void cpu::push(word value)
{
    mem.store<word>(SP.load(), value);
    SP.store(SP.load()-2);
}

word cpu::pop()
{
    SP.store(SP.load() + 2);
    return mem.load<word>(SP.load());   
}

void cpu::jump(word address)
{
    PC = address;
}

cpu::cpu() : 
    _sp_value_low(0),
    _sp_value_high(0),
    _operands(std::make_unique<::operands>(*this)),
    A("A"),
    B("B"),
    C("C"),
    D("D"),
    E("E"),
    F(),
    H("H"),
    L("L"),
    AF("AF", F.address(), A.address()),
    BC("BC", C.address(), B.address()),
    DE("DE", E.address(), D.address()),
    HL("HL", L.address(), H.address()),
    SP("SP", &_sp_value_low, &_sp_value_high), PC(0)
{
}


void cpu::run()
{
    while (true)
    {
        next();
    }
}

void cpu::set(byte* val, byte bit_place)
{
    *val |= 1 << bit_place;
}

void cpu::res(byte* val, byte bit_place)
{
    *val &= ~(1 << bit_place);
}

void cpu::add(byte* val, byte n, bool carry)
{
    byte new_value = *val + n;

    if (carry)
    {
        new_value += F.carry() ? 1 : 0;
    }

    F.zero(*val == 0);
    F.substract(false);
    F.carry(new_value < *val);
    F.half_carry((new_value & 0xF) < (*val & 0xF));
    *val = new_value;
}

void cpu::adc(byte* val, byte n)
{
    add(val, n, true);
}

void cpu::sbc(byte* val, byte n)
{
    sub(val, n, true);
}

void cpu::and_n(byte* val, byte n)
{
    *val &= n;
    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(true);
    F.carry(false);
}

void cpu::or_n(byte* val, byte n)
{
    *val |= n;
    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(false);
    F.carry(false);
}

void cpu::xor_n(byte* a, byte byte)
{
    *a ^= byte;
    F.zero(*a == 0);
    F.substract(false);
    F.half_carry(false);
    F.carry(false);
}

void cpu::cp(byte val, byte byte)
{
    sub(&val, byte, false, false);
}

void cpu::inc(byte* val)
{
    F.half_carry((*val & 0xF) == 0b1111);
    (*val)++;
    F.zero(*val == 0);
    F.substract(false);
}

void cpu::dec(byte* val)
{
    F.half_carry((*val >> 4) == 0b0001);
    (*val)--;
    F.zero(*val == 0);
    F.substract(true);
}

void cpu::swap(byte* val)
{
    *val = *val >> 4 | *val << 4;
    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(false);
    F.carry(false);
}

cpu::~cpu() = default;

void cpu::sub(byte* val, byte n, bool carry, bool save_result)
{
    byte new_value = *val - n;

    if (carry)
    {
        new_value -= F.carry_bit();
    }

    F.zero(new_value == 0);
    F.substract(false);
    F.carry(new_value > *val);
    F.half_carry((new_value & 0xF) > (*val & 0xF));

    if (save_result)
    {
        *val = new_value;
    }
}

void cpu::next()
{
}

void cpu::halt()
{
}

void cpu::stop()
{
}

void cpu::error()
{
}


void cpu::ccf()
{
    F.carry(!F.carry());
    F.half_carry(false);
    F.substract(false);
}

void cpu::scf()
{
    F.half_carry(false);
    F.substract(false);
    F.carry(true);
}

void cpu::rla()
{
    rl(A.address());
}

void cpu::rlca()
{
    rlc(A.address());
}

void cpu::rrca()
{
    rrc(A.address());
}

void cpu::rra()
{
    rr(A.address());
}

void cpu::bit(byte val, byte bitPlace)
{
    F.zero(!(val & (1 << bitPlace)));
    F.substract(false);
    F.half_carry(true);
}

void cpu::rl(byte* val)
{
    F.carry((*val & (1 << 7)));
    *val = (*val << 1) | F.carry_bit();
    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(false);
}

void cpu::rlc(byte* val)
{
    byte old_carry = F.carry_bit();
    F.carry(*val & (1 << 7) ? 1 : 0);
    *val = (*val << 1) | old_carry;

    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(false);
}

void cpu::rrc(byte* val)
{
    byte old_carry = F.carry_bit();
    F.carry(*val & 1);
    *val = (*val >> 1) | (old_carry << 7);

    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(false);
}

void cpu::rr(byte* val)
{
    F.carry(*val & 1);
    *val = (*val >> 1) | (F.carry_bit() << 7);

    // update flags
    F.half_carry(false);
    F.substract(false);
    F.zero(*val == 0);
}

void cpu::sla(byte* val)
{
    F.carry(*val & 128);
    *val <<= 1;
    F.zero(*val == 0);
    F.half_carry(false);
    F.substract(false);

}

void cpu::sra(byte* val)
{
    F.carry(*val & 1);
    *val = ((char)*val) >> 1;

    F.zero(*val == 0);
    F.half_carry(false);
    F.substract(false);
}

void cpu::srl(byte* val)
{
    F.carry(*val & 1);
    *val >>= 1;

    F.zero(*val == 0);
    F.half_carry(false);
    F.substract(false);
}