#pragma once
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/base_instructions/register_instruction.h>
#include <GameKid/opcodes.h>

class and_instruction : public register_instruction
{
public:
    explicit and_instruction(cpu& cpu);
    void run(byte* val) override;
};

and_instruction::and_instruction(cpu& cpu) : register_instruction(cpu, "and", false,
    AND_A_A,
    AND_A_B,
    AND_A_C,
    AND_A_D,
    AND_A_E,
    AND_A_H,
    AND_A_L)
{
}

void and_instruction::run(byte* val)
{
    _cpu.and_n(&_cpu.A, *val);
}