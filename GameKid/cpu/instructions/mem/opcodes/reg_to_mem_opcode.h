#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"

class reg_to_mem_opcode : public opcode
{
private:
    reg8 _src;
    reg16 _dst_mem;
public:
    reg_to_mem_opcode(cpu& cpu, const reg8& src, const reg16& dst_mem, byte value)
        : opcode(cpu, "ld", value, false, 8), _src(src), _dst_mem(dst_mem)
    {
    }

    void run() override
    {
        _cpu.mem.store(_dst_mem.get(), *_src.address);

    }

    std::string to_str(byte* next) override
    {
        return name + " [" + _dst_mem.name + "], " + _src.name;
    }
};
