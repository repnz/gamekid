#pragma once
#include <sstream>
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/opcode.h"

class imm_to_reg_opcode : public opcode
{
private:
    reg _reg;
public:
    imm_to_reg_opcode(cpu& cpu, const reg& reg, byte value)
        : opcode(cpu, "ld", value, false, 8), _reg(reg)
    {
    }

    void run() override
    {
        *_reg.address = _cpu.mem.load_byte(_cpu.PC + 1);

    }

    std::string to_str(byte* next) override
    {
        std::stringstream ss;
        ss << name << " " << _reg.name << ", " << *next;
        return ss.str();
    }
};
