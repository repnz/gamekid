#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"
#include <sstream>

class imm_to_hl_opcode : public opcode
{
public:
    explicit imm_to_hl_opcode(cpu& cpu)
        : opcode(cpu, "ld", 0x36, false, 12)
    {
    }

    void run() override
    {
        const byte immidiate = _cpu.mem.load_byte(_cpu.PC + 1);
        _cpu.mem.store(_cpu.regs.HL.get(), immidiate);
    }

    std::string to_str(byte* next) override
    {
        std::stringstream ss;
        ss << name << " [HL], " << *next;
        return ss.str();
    }
};
