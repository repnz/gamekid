#pragma once
#include "GameKid/cpu/instruction_set.h"

class rotation
{
public:
    static void initialize(instruction_set& set, cpu& cpu);
    static void rl_operation(cpu& cpu, operand<byte>& op);
    static void rla_operation(cpu& cpu);
    static void rr_operation(cpu& cpu, operand<byte>& op);
    static void rra_operation(cpu& cpu);
    static void rlc_operation(cpu& cpu, operand<byte>& op);
    static void rlca_operation(cpu& cpu);
    static void rrc_operation(cpu& cpu, operand<byte>& op);
    static void rrca_operation(cpu& cpu);
    static void sla_operation(cpu& cpu, operand<byte>& op);
    static void srl_operation(cpu& cpu, operand<byte>& op);
    static void sra_operation(cpu& cpu, operand<byte>& op);
};
