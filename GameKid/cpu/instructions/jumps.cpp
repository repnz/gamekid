#include "jumps.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/operands.h>

void jump_absolute_operation(cpu& cpu, operand<word>& address)
{
    cpu.jump(address.load());
}

void jump_absolute_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<word>& address)
{
    if (condition.load())
    {
        cpu.jump(address.load());
    }
}

void jumps::initialize(cpu & cpu, instruction_set & set)
{
    set.add_instruction(instruction_builder(cpu, "jp")
        .operands(cpu.operands().immidiate_word())
            .opcode(0xC3)
            .cycles(12)
            .operation(jump_absolute_operation)
            .add()
        .operands(cpu.operands().nz(), cpu.operands().immidiate_word())
            .opcode(0xC2)
            .cycles(12)
            .operation(jump_absolute_with_condition_operation)
            .add()
        .operands(cpu.operands().z(), cpu.operands().immidiate_word())
            .opcode(0xCA)
            .cycles(12)
            .operation(jump_absolute_with_condition_operation)
            .add()
        .operands(cpu.operands().nc(), cpu.operands().immidiate_word())
            .opcode(0xD2)
            .cycles(12)
            .operation(jump_absolute_with_condition_operation)
            .add()
        .operands(cpu.operands().c(), cpu.operands().immidiate_word())
            .opcode(0xDA)
            .cycles(12)
            .operation(jump_absolute_with_condition_operation)
            .add()
        .build());
}
