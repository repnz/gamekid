#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"

const byte DAA = 0x27;

class daa_instruction : public single_opcode_instruction
{    
public:
    explicit daa_instruction(cpu& cpu)
        : single_opcode_instruction(cpu, "daa", DAA, false, 4)
    {
    }

    void run() override
    {
        const byte left_digit = (_cpu.A & 0xF0) >> 4;
        const byte right_digit = (_cpu.A & 0x0F);

        if (left_digit > 10 || right_digit > 10)
        {
            // Error, what to do?
        }

        _cpu.A = left_digit * 10 + right_digit;
        _cpu.set_zero_flag(_cpu.A);
        _cpu.substruct_flag = 0;
        // what should be done with the carry flag?
    }
};
