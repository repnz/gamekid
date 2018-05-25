#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"

class reg_to_reg16_mem_opcode : public opcode
{
private:
    reg8 _dst;
    reg16 _src_mem;
public:
    reg_to_reg16_mem_opcode(cpu& cpu, const reg8& src, const reg16& dst_mem, byte value)
        : opcode(cpu, "ld", value, false, 8), _dst(src), _src_mem(dst_mem)
    {
    }

    void run() override
    {
        _cpu.mem.store(_src_mem.get(), *_dst.address);

    }

    std::string to_str(byte* next) override
    {
        return name + " [" + _src_mem.name + "], " + _dst.name;
    }
};
