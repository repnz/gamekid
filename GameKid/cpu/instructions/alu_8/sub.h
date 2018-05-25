#pragma once
#include "GameKid/cpu.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class sub_instruction : public register_instruction
{
public:
    explicit sub_instruction(cpu& cpu);
    void run(byte* val) override;
};

sub_instruction::sub_instruction(cpu& cpu) : register_instruction(cpu, "sub", false,
    { SUB_A_A,
    SUB_A_B,
    SUB_A_C,
    SUB_A_D,
    SUB_A_E,
    SUB_A_H,
    SUB_A_L })
{
}

void sub_instruction::run(byte* val)
{
    _cpu.sub(_cpu.regs.A.address, *val);
}