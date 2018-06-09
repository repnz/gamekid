#include "jumps.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/operands.h>

void jp_operation(cpu& cpu, operand<word>& address)
{
    cpu.jump(address.load());
}

void jp_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<word>& address)
{
    if (condition.load())
    {
        jp_operation(cpu, address);
    }
}

void jr_operation(cpu& cpu, operand<byte>& offset)
{
    char value = static_cast<char>(offset.load());
    cpu.PC += value;
    cpu.jump(cpu.PC);
}

void jr_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<byte>& offset)
{
    if (condition.load())
    {
        jr_operation(cpu, offset);
    }
}

void jumps::initialize(cpu & cpu, instruction_set & set)
{
    set.add_instruction(instruction_builder(cpu, "jp")
        .operands(cpu.operands().immidiate_word())
            .opcode(0xC3)
            .cycles(12)
            .operation(jp_operation)
            .add()
        .operands(cpu.operands().nz(), cpu.operands().immidiate_word())
            .opcode(0xC2)
            .cycles(12)
            .operation(jp_with_condition_operation)
            .add()
        .operands(cpu.operands().z(), cpu.operands().immidiate_word())
            .opcode(0xCA)
            .cycles(12)
            .operation(jp_with_condition_operation)
            .add()
        .operands(cpu.operands().nc(), cpu.operands().immidiate_word())
            .opcode(0xD2)
            .cycles(12)
            .operation(jp_with_condition_operation)
            .add()
        .operands(cpu.operands().c(), cpu.operands().immidiate_word())
            .opcode(0xDA)
            .cycles(12)
            .operation(jp_with_condition_operation)
            .add()
        .operands(cpu.operands().hl_addressing())
            .opcode(0xE9)
            .cycles(4)
            .operation(jp_operation)
            .add()
        .build());

    set.add_instruction(instruction_builder(cpu, "jr")
        .operands(cpu.operands().immidiate_byte())
            .opcode(0x18)
            .cycles(8)
            .operation(jr_operation)
            .add()
        .operands(cpu.operands().nz(), cpu.operands().immidiate_byte())
            .opcode(0x20)
            .cycles(8)
            .operation(jr_with_condition_operation)
            .add()
        .operands(cpu.operands().z(), cpu.operands().immidiate_byte())
            .opcode(0x28)
            .cycles(8)
            .operation(jr_with_condition_operation)
            .add()
        .operands(cpu.operands().nc(), cpu.operands().immidiate_byte())
            .opcode(0x30)
            .cycles(8)
            .operation(jr_with_condition_operation)
            .add()
        .operands(cpu.operands().c(), cpu.operands().immidiate_byte())
            .opcode(0x38)
            .cycles(8)
            .operation(jr_with_condition_operation)
            .add()
        .build());
}
