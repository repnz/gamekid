#pragma once
#include <GameKid/cpu/instruction_set.h>

class misc
{
public:
    static void initialize(cpu& cpu, instruction_set& set);
    static void swap_operation(cpu& cpu, operand<byte>& op);
    static void cpl_operation(cpu& cpu);
    static void nop_operation(cpu& cpu);
    static void scf_operation(cpu& cpu);
    static void stop_operation(cpu& cpu);
    static void daa_operation(cpu& cpu);
    static void ccf_operation(cpu& cpu);
    static void halt_operation(cpu& cpu);
    static void ei_operation(cpu& cpu);
    static void di_operation(cpu& cpu);

};
