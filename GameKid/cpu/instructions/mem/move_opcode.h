#pragma once
#include <GameKid/cpu/opcode.h>
#include <GameKid/cpu/operand.h>
#include <functional>

template <typename move_type>
class move_opcode : public opcode
{

private:
    const source_operand<move_type>& _src;
    dest_operand<move_type>& _dst;
public:
    move_opcode(std::string name, cpu& cpu, byte value, byte cycles, 
        const source_operand<move_type>& src,
        dest_operand<move_type>& dst) :
    opcode(cpu, name, value, false, cycles), _src(src), _dst(dst)
    {
    }

    void run() override
    {
        _dst.store(_src.load());
    }

    std::string to_str(byte* next) override
    {
        return name + _dst.to_str(next) + ", " + _src.to_str(next);
    }

    std::vector<byte> bytes(const std::vector<std::string>& operands) override
    {
        std::vector<byte> v;
        v.push_back(value);
        
        for (byte opcode_byte : _src.bytes(operands[0]))
        {
            v.push_back(opcode_byte);
        }
        for (byte opcode_byte : _dst.bytes(operands[1]))
        {
            v.push_back(opcode_byte);
        }

        return v;
    }
};
