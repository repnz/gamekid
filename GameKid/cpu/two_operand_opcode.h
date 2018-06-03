#pragma once
#include "opcode.h"
#include <functional>

template <typename operand_type>
class two_operand_opcode : public opcode
{
private:
    std::function<void(operand<operand_type>&, operand<operand_type>&)> _act;
    operand<operand_type>& _first_operand;
    operand<operand_type>& _second_operand;
public:
    two_operand_opcode(cpu& cpu, const std::string& name, const std::vector<byte>& value, byte cycles, 
        operand<operand_type>& first,
        operand<operand_type>& second,
        std::function<void(operand<operand_type>&, operand<operand_type>&)> act)
        : opcode(cpu, name, value, cycles), _act(act), _first_operand(first), _second_operand(second)
    {
    }

    void run() override
    {
        _act(_first_operand, _second_operand);
    }

    std::vector<byte> bytes(const std::vector<std::string>& operands) override
    {
        std::vector<byte> v;

        for (byte opcode_byte : value)
        {
            v.push_back(opcode_byte);
        }

        for (byte opcode_byte : _first_operand.bytes(operands[0]))
        {
            v.push_back(opcode_byte);
        }

        for (byte opcode_byte : _second_operand.bytes(operands[1]))
        {
            v.push_back(opcode_byte);
        }

        return v;
    }
};
