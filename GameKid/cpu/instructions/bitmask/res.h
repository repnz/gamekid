#pragma once
#include "GameKid/cpu/base_instructions/bitmask_instruction.h"
#include "GameKid/opcodes.h"


class res_instruction : public bitmask_instruction
{
public:
    explicit res_instruction(cpu& cpu)
        : bitmask_instruction(cpu, "res",
            CB_RES_b_A,
            CB_RES_b_B,
            CB_RES_b_C,
            CB_RES_b_D,
            CB_RES_b_E,
            CB_RES_b_H,
            CB_RES_b_L)
    {
    }

    void run(byte* val, byte bit) override
    {
        _cpu.res(val, bit);
    }
};

