#pragma once
#include "GameKid/opcodes.h"
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"

class cp_instruction : public register_instruction
{
public:
    explicit cp_instruction(cpu& cpu);
    void run(byte* val) override;
};

cp_instruction::cp_instruction(cpu& cpu) : register_instruction(cpu, "cp", false,
    { CP_A_A,
    CP_A_B,
    CP_A_C,
    CP_A_D,
    CP_A_E,
    CP_A_H,
    CP_A_L })
{
}

void cp_instruction::run(byte* val)
{
    _cpu.or_n(&_cpu.A, *val);
}

