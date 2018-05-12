#pragma once
#include "GameKid/opcodes.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"

class srl_instruction : public register_instruction
{
public:
    explicit srl_instruction(cpu& cpu)
        : register_instruction(cpu, "srl", true,
            CB_SRL_A,
            CB_SRL_B,
            CB_SRL_C,
            CB_SRL_D,
            CB_SRL_E,
            CB_SRL_H,
            CB_SRL_L)
    {
    }

    void run(byte* val) override
    {
        _cpu.srl(val);
    }
};
