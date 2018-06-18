#pragma once
#include <GameKid/cpu/instruction_set.h>

class mem
{
public:
    static void push(cpu& cpu, word value);
    static word pop(cpu& cpu);

    static void ldd_operation(cpu& cpu, operand<byte>& dst, operand<byte>& src);
    static void push_operation(cpu& cpu, operand<word>& dst);
    static void pop_operation(cpu& cpu, operand<word>& dst);
    static void initialize(cpu& cpu, instruction_set& set);
};
