#include <GameKid/cpu.h>
#include "cpu/operands.h"


void cpu::schedule_operation(cpu_operation<> operation, int instruction_count)
{
    _scheduled_operations.emplace_back(operation, instruction_count);
}

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

void cpu::enable_interrupts()
{
    _interrupts_enabled = true;
}

void cpu::disable_interrupts()
{
    _interrupts_enabled = false;
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
    SP("SP", &_sp_value_low, &_sp_value_high), PC(0), _interrupts_enabled(false)
{
}


void cpu::run()
{
    while (true)
    {
        next();
    }
}


void cpu::swap(byte* val)
{
    *val = *val >> 4 | *val << 4;
    F.zero(*val == 0);
    F.substract(false);
    F.half_carry(false);
    F.carry(false);
}

bool cpu::check_carry_up(word before, word after, byte bit_place)
{
    const word bits = (1 << bit_place);
    return (before & bits) < (after & bits);
}

bool cpu::check_carry_down(word before, word after, byte bit_place)
{
    const word bits = (1 << bit_place);
    return (before & bits) > (after & bits);
}

cpu::~cpu() = default;

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