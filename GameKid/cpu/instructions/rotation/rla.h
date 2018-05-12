#pragma once
#include <string>
#include <vector>
#include "GameKid/cpu.h"
#include "GameKid/opcodes.h"
#include "GameKid/cpu/opcode.h"
#include <GameKid/cpu/instruction.h>

class rla_opcode : public opcode
{
public:
    explicit rla_opcode(cpu& cpu)
        : opcode(cpu, "rla", RLA, false, 4)
    {
    }

    void run() override
    {
        _cpu.rla();
    }
};

class rla_instruction : public instruction
{
private:
    rla_opcode _opcode;
public:
    explicit rla_instruction(cpu& cpu) : instruction(cpu, "rla"), _opcode(cpu)
    {
        opcodes.push_back(&_opcode);
    }


    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        if (operands.size() != 0) { return {}; }

        return { _opcode.value };
    }
};
