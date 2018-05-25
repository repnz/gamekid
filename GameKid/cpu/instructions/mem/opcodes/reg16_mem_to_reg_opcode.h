#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"

class reg16_mem_to_reg_opcode : public opcode
{
private:
    reg16 _src_mem;
    reg8 _dst;
public:
    reg16_mem_to_reg_opcode(cpu& cpu, const reg16& src_mem, const reg8& dst, byte value)
        : opcode(cpu, "ld", value, false, 8), _src_mem(src_mem), _dst(dst)
    {
    }

    void run() override
    {
        _dst.set(_cpu.mem.load_byte(_src_mem.get()));

    }

    std::string to_str(byte* next) override
    {
        return name + " " + _dst.name + ", [" + _src_mem.name + "]";
    }
};
