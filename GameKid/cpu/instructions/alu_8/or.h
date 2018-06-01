#pragma once
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class or_instruction : public register_instruction
{
public:
    explicit or_instruction(cpu& cpu);
    void run(byte* val) override;
};

or_instruction::or_instruction(cpu& cpu) : register_instruction(cpu, "or", false,
    { OR_A_A,
    OR_A_B,
    OR_A_C,
    OR_A_D,
    OR_A_E,
    OR_A_H,
    OR_A_L })
{
}

void or_instruction::run(byte* val)
{
    _cpu.or_n(_cpu.A.address(), *val);
}