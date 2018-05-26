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
        byte moved_byte = _src.load();
        _dst.store(moved_byte);
    }

    std::string to_str(byte* next) override
    {
        return "ld " + _dst.to_str(next) + ", " + _src.to_str(next);
    }
};