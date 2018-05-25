#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"

class reg_to_hl_opcode : public opcode
{
private:
    reg _reg;
public:
    reg_to_hl_opcode(cpu& cpu, const reg& reg, byte value)
        : opcode(cpu, "ld", value, false, 8), _reg(reg)
    {
    }

    void run() override
    {
        _cpu.mem.store(_cpu.HL(), *_reg.address);

    }

    std::string to_str(byte* next) override
    {
        return name + " [HL], " + _reg.name;
    }
};
