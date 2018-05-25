#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"

class a_to_c_mem_opcode : public opcode
{
public:
    explicit a_to_c_mem_opcode(cpu& cpu)
        : opcode(cpu, "ld", 0xE2, false, 8)
    {
    }

    void run() override
    {
        const word address = _cpu.regs.C.get() + 0xFF00;
        _cpu.mem.store(address, _cpu.regs.A.get());

    }

    std::string to_str(byte* next) override
    {
        return "ld [c], A";
    }
};
