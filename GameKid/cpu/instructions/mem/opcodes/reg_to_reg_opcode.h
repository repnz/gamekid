#pragma once
#include "GameKid/cpu/opcode.h"

class reg_to_reg_opcode : public opcode
{
private:
    reg src;
    reg dst;
public:
    reg_to_reg_opcode(cpu& cpu, const std::string& name, byte value, const reg& src, const reg& dst, byte cycles)
        : opcode(cpu, name, value, false, cycles), src(src), dst(dst)
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
