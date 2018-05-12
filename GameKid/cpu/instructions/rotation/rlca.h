#pragma once
#include "GameKid/cpu.h"
#include "GameKid/cpu/opcode.h"
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction.h"

class rlca_opcode : public opcode
{
public:
    explicit rlca_opcode(cpu& cpu)
        : opcode(cpu, "rlca", RLCA, false, 4)
    {
    }

    void run() override
    {
        _cpu.rlca();
    }
};

class rlca_instruction : public instruction
{
private:
    rlca_opcode _opcode;
public:
    explicit rlca_instruction(cpu& cpu) : instruction(cpu, "rlca"), _opcode(cpu)
    {
        opcodes.push_back(&_opcode);
    }

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        if (operands.size() != 0) { return {}; }

        return { _opcode.value };
    }

};
