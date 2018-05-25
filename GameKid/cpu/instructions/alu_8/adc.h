#pragma once
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"


class adc_instruction : public register_instruction
{
public:
    explicit adc_instruction(cpu& cpu);
    void run(byte* val) override;
};


adc_instruction::adc_instruction(cpu& cpu) : register_instruction(cpu, "adc", false,
    { ADC_A_A,
    ADC_A_B,
    ADC_A_C,
    ADC_A_D,
    ADC_A_E,
    ADC_A_H,
    ADC_A_L })
{
}

void adc_instruction::run(byte* val)
{
    _cpu.add(_cpu.regs.A.address, *val, true);
}
