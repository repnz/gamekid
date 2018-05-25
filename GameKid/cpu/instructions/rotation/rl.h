#pragma once
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class rl_instruction : public register_instruction
{
public:
    explicit rl_instruction(cpu& cpu)
        : register_instruction(cpu, "rl", true,
            { CB_RL_A,
            CB_RL_B,
            CB_RL_C,
            CB_RL_D,
            CB_RL_E,
            CB_RL_H,
            CB_RL_L })
    {
    }

    void run(byte* val) override
    {
        _cpu.rl(val);
    }
};
