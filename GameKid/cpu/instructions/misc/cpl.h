#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"

const byte CPL = 0x2F;

class cpl_instruction : public single_opcode_instruction
{
public:
    explicit cpl_instruction(cpu& cpu)
        : single_opcode_instruction(cpu, "cpl", CPL, false, 4)
    {
    }

    void run() override
    {
        _cpu.A = ~_cpu.A;
        _cpu.half_carry_flag = 1;
        _cpu.substruct_flag = 1;
    }
};
