#pragma once
#include <string>
#include <vector>
#include "GameKid/cpu.h"
#include "GameKid/cpu/opcode.h"
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction.h"

class rra_opcode : public opcode
{
public:
    explicit rra_opcode(cpu& cpu)
        : opcode(cpu, "rra", RRA, false, 4)
    {
    }

    void run() override
    {
        _cpu.rla();
    }
};

class rra_instruction : public instruction
{
private:
    rra_opcode _opcode;
public:
    explicit rra_instruction(cpu& cpu) : instruction(cpu, "rra"), _opcode(cpu)
    {
        opcodes.push_back(&_opcode);
    }

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        if (operands.size() != 0) { return {}; }

        return { _opcode.value };
    }
};
