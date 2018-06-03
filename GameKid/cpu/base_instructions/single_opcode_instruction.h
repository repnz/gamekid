#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_opcodes/function_opcode.h"

class single_opcode_instruction : public instruction
{
private:
    function_opcode _op;
public:

    single_opcode_instruction(cpu& cpu, const std::string& name, 
        const std::vector<byte>& value, byte cycles, const std::function<void()>& function)
        : instruction(cpu, name),
        _op(function_opcode(_cpu, name, value, cycles, function))
    {
    }

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        return _op.bytes(operands);
    }
};
