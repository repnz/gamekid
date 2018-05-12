#pragma once
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class sbc_instruction : public register_instruction
{
public:
    explicit sbc_instruction(cpu& cpu);
    void run(byte* val) override;
};

inline sbc_instruction::sbc_instruction(cpu& cpu) : register_instruction(cpu, "sbc", false,
    SBC_A_A,
    SBC_A_B,
    SBC_A_C,
    SBC_A_D,
    SBC_A_E,
    SBC_A_H,
    SBC_A_L)
{
}

inline void sbc_instruction::run(byte* val)
{
    _cpu.sub(&_cpu.A, *val, true);
}
