#pragma once
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class xor_instruction : public register_instruction
{
public:
    explicit xor_instruction(cpu& cpu);
    void run(byte* val) override;
};

xor_instruction::xor_instruction(cpu& cpu) : register_instruction(cpu, "xor", false,
    { XOR_A_A,
    XOR_A_B,
    XOR_A_C,
    XOR_A_D,
    XOR_A_E,
    XOR_A_H,
    XOR_A_L })
{
}

void xor_instruction::run(byte* val)
{
    _cpu.xor_n(&_cpu.A, *val);
}
