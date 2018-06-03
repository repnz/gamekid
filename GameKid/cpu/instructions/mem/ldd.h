#pragma once
#include "GameKid/cpu/instruction.h"
#include "move_opcode.h"
#include "mem_operands.h"

class ldd_instruction : instruction
{
private:
    reg_mem_operand _hl_mem;
    move_opcode<byte> _a_to_hl;
    move_opcode<byte> _hl_to_a;
public:
    ldd_instruction(cpu& cpu, const std::string& name)
        : instruction(cpu, name),
    _hl_mem(cpu.mem, cpu.HL),
        _a_to_hl("ldd", cpu, 0x32, 8, cpu.A, _hl_mem, [](byte b) {return b - 1 }),
    _hl_to_a("ldd", cpu, 0x32, 8, _hl_mem, cpu.A)
    {
    }

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        return {};
    }
};
