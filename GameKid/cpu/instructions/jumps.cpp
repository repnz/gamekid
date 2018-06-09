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

void call_operation(cpu& cpu, operand<word>& address)
{
    cpu.push(cpu.PC+1);
    cpu.PC = address.load();
}

void call_with_condition_operation(cpu& cpu, operand<bool>& condition, operand<word>& address)
{
    if (condition.load())
    {
        call_operation(cpu, address);
    }
}

void rst_operation(cpu& cpu, operand<byte>& address)
{
    cpu.push(cpu.PC);
    cpu.jump(address.load());
}


void ret_operation(cpu& cpu)
{
    cpu.jump(cpu.pop());
}

void ret_with_condition_operation(cpu& cpu, operand<bool>& condition)
{
    if (condition.load())
    {
        ret_operation(cpu);
    }
}

void reti_operation(cpu& cpu)
{
    ret_operation(cpu);
    cpu.enable_interrupts();
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


    set.add_instruction(instruction_builder(cpu, "call")
        .operands(cpu.operands().immidiate_word())
            .opcode(0xCD)
            .cycles(12)
            .operation(call_operation)
            .add()
        .operands(cpu.operands().nz(), cpu.operands().immidiate_word())
            .opcode(0xC4)
            .cycles(12)
            .operation(call_with_condition_operation)
            .add()
        .operands(cpu.operands().z(), cpu.operands().immidiate_word())
            .opcode(0xCC)
            .cycles(12)
            .operation(call_with_condition_operation)
            .add()
        .operands(cpu.operands().nc(), cpu.operands().immidiate_word())
            .opcode(0xD4)
            .cycles(12)
            .operation(call_with_condition_operation)
            .add()
        .operands(cpu.operands().c(), cpu.operands().immidiate_word())
            .opcode(0xDC)
            .cycles(12)
            .operation(call_with_condition_operation)
            .add()
        .build());

    instruction_builder rst_builder(cpu, "rst");

    for (int i=0x00; i<=0x38; ++i)
    {
        rst_builder
            .operands(cpu.operands().constant(i))
            .opcode(0xC7 + i)
            .cycles(32)
            .operation(rst_operation)
            .add();
    }

    set.add_instruction(rst_builder.build());

    set.add_instruction(instruction_builder(cpu, "ret")
        .operands()
            .opcode(0xC9)
            .cycles(0x8)
            .operation(ret_operation)
            .add()
        .operands(cpu.operands().nz())
            .opcode(0xC0)
            .cycles(0x8)
            .operation(ret_with_condition_operation)
            .add()
        .operands(cpu.operands().z())
            .opcode(0xC8)
            .cycles(0x8)
            .operation(ret_with_condition_operation)
            .add()
        .operands(cpu.operands().nc())
            .opcode(0xD0)
            .cycles(0x8)
            .operation(ret_with_condition_operation)
            .add()
        .operands(cpu.operands().c())
            .opcode(0xD8)
            .cycles(0x8)
            .operation(ret_with_condition_operation)
            .add()
        .build());

    set.add_instruction(instruction_builder(cpu, "reti")
        .operands()
            .opcode(0xD9)
            .cycles(8)
            .operation(reti_operation)
            .add()
        .build());
}
