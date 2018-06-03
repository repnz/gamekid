#pragma once
#include "opcode.h"
#include <functional>

template <typename operand_type>
class single_operand_opcode : public opcode
{
private:
    std::function<void(operand<operand_type>&)> _act;
    operand<operand_type>& _operand;
public:
    single_operand_opcode(cpu& cpu, const std::string& name, const std::vector<byte>& value, byte cycles,
        operand<operand_type>& op,
        std::function<void(operand<operand_type>&)> act)
        : opcode(cpu, name, value, cycles), _act(act), _operand(op)
    {
    }

    void run() override
    {
        _act(_operand);
    }

    std::vector<byte> bytes(const std::vector<std::string>& operands) override
    {
        std::vector<byte> v;
        
        for (byte opcode_byte : value)
        {
            v.push_back(opcode_byte);
        }
        
        for (byte opcode_byte : _operand.bytes(operands[0]))
        {
            v.push_back(opcode_byte);
        }

        return v;
    }
    
    std::string to_str(byte* next) override
    {
        return name + _operand.to_str(next);
    }
};
