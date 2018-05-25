#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu/opcode.h"
#include <sstream>

class a_to_imm_mem_opcode : public opcode
{
public:
    explicit a_to_imm_mem_opcode(cpu& cpu)
        : opcode(cpu, "ld", 0xEA, false, 16)
    {
    }

    void run() override
    {
        const word address = _cpu.mem.load_word_le(_cpu.PC + 1);
        _cpu.mem.store(address, _cpu.regs.A.get());

    }

    std::string to_str(byte* next) override
    {
        std::stringstream ss;
        ss << "ld [" << std::hex << *(word*)next << ", A";
        return ss.str();
    }
};
