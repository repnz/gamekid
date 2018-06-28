#include <GameKid/cpu.h>
#include "cpu/operands.h"

cpu::cpu(const std::vector<byte>& rom) :
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
    SP("SP", &_sp_value_low, &_sp_value_high), PC(0), _interrupts_enabled(false),
    mem(rom)
{
}

cpu::cpu() : cpu(std::vector<byte>{}) 
{
}

void cpu::schedule_operation(cpu_operation<> operation, int instruction_count)
{
    _scheduled_operations.emplace_back(operation, instruction_count);
}

operands& cpu::operands()
{
    return *_operands.get();
}

void cpu::enable_interrupts()
{
    _interrupts_enabled = true;
}

void cpu::disable_interrupts()
{
    _interrupts_enabled = false;
}

void cpu::run()
{
    while (true)
    {
        next();
    }
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