#pragma once
#include "GameKid/cpu/operand.h"
#include <functional>
class cpu;
class instruction_set;

class jumps
{
public:
    static void initialize(cpu& cpu, instruction_set& set);
    static void jp_operation(cpu& cpu, operand<word>& address);
    static void jp_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<word>& address);
    static void jr_operation(cpu& cpu, operand<byte>& offset);
    static void jr_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<byte>& offset);
    static void call_operation(cpu& cpu, operand<word>& address);
    static void call_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<word>& address);
    static void rst_operation(cpu& cpu, operand<byte>& address);
    static void ret_operation(cpu& cpu);
    static void ret_with_condition_operation(cpu& cpu, operand<bool>& condition);
    static void reti_operation(cpu& cpu);

};