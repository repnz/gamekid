#pragma once
#include <GameKid/cpu/base_instructions/register_instruction.h>
#include "GameKid/opcodes.h"

class swap_instruction : public register_instruction
{
public:
    explicit swap_instruction(cpu& cpu)
        : register_instruction(cpu, "swap", true,
            CB_SWAP_A,
            CB_SWAP_B,
            CB_SWAP_C,
            CB_SWAP_D,
            CB_SWAP_E,
            CB_SWAP_H,
            CB_SWAP_L)
    {
    }

    void run(byte* val) override
    {
        _cpu.swap(val);
    }
};
