#pragma once
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class rr_instruction : public register_instruction
{
public:
    explicit rr_instruction(cpu& cpu)
        : register_instruction(cpu, "rr", true,
            { CB_RR_A,
            CB_RR_B,
            CB_RR_C,
            CB_RR_D,
            CB_RR_E,
            CB_RR_H,
            CB_RR_L })
    {
    }

    void run(byte* val) override
    {
        _cpu.rr(val);
    }
};
