#pragma once
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class add_instruction : public register_instruction
{
public:
    explicit add_instruction(cpu& cpu);
    void run(byte* val) override;
};

add_instruction::add_instruction(cpu& cpu) : register_instruction(cpu, "add", false,
    { ADD_A_A,
    ADD_A_B,
    ADD_A_C,
    ADD_A_D,
    ADD_A_E,
    ADD_A_H,
    ADD_A_L })
{
}

void add_instruction::run(byte* val)
{
    _cpu.add(&_cpu.A, *val);
}
