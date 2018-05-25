#pragma once

class sra_instruction : public register_instruction
{
public:
    explicit sra_instruction(cpu& cpu)
        : register_instruction(cpu, "sla", true,
            { CB_SLA_A,
            CB_SLA_B,
            CB_SLA_C,
            CB_SLA_D,
            CB_SLA_E,
            CB_SLA_H,
            CB_SLA_L })
    {
    }

    void run(byte* val) override
    {
        _cpu.sra(val);
    }
};