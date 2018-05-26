#pragma once
#include <GameKid/cpu/opcode.h>

template <typename source_operand_type, typename dest_operand_type>
//    requires source_operand && dest_operand
class move_opcode : public opcode
{

private:
    source_operand_type _src;
    dest_operand_type _dst;
public:
    move_opcode(cpu& cpu, byte value, byte cycles, const source_operand_type& src, const dest_operand_type& dst) :
    opcode(cpu, "ld", value, false, cycles), _src(src), _dst(dst)
    {
    }

    void run() override
    {
        _dst.store(_src.load());
    }

    std::string to_str(byte* next) override
    {
        return "ld " + _dst.to_str(next) + ", " + _src.to_str(next);
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