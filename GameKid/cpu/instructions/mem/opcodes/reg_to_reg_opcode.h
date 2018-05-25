#pragma once
#include "GameKid/cpu/opcode.h"

class reg_to_reg_opcode : public opcode
{
private:
    reg8 src;
    reg8 dst;
public:
    reg_to_reg_opcode(cpu& cpu, byte value, const reg8& src, const reg8& dst)
        : opcode(cpu, "ld", value, false, 4), src(src), dst(dst)
    {
    }

    void run() override
    {
        *dst.address = *src.address;
    }

    std::string to_str(byte* next) override
    {
        return name + " " + dst.name + ", " + src.name;
    }
};
