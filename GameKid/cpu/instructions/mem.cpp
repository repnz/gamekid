#include "mem.h"
#include "mem/ld.h"
#include <GameKid/cpu/instruction_set.h>

void mem::ldd_operation(cpu& cpu, operand<byte>& dst, operand<byte>& src)
{
    dst.store(src.load());
}

void mem::push(cpu& cpu, word value) 
{
    cpu.mem.store<word>(cpu.SP.load(), value);
    cpu.SP.store(cpu.SP.load() - 2);
}

void mem::push_operation(cpu& cpu, operand<word>& dst)
{
    const word value_to_push = dst.load();
    push(cpu, value_to_push);
}

word mem::pop(cpu& cpu) 
{
    // increment the stack pointer
    cpu.SP.store(cpu.SP.load() + 2);

    // load the value from the stack
    return cpu.mem.load<word>(cpu.SP.load());
}

void mem::pop_operation(cpu& cpu, operand<word>& dst)
{
    dst.store(pop(cpu));

}

void mem::initialize(cpu& cpu, instruction_set& set)
{
    set.add_instruction(std::make_unique<ld_instruction>(cpu));

    set.add_instruction(
        instruction_builder(cpu, "ldd")
        .operands(cpu.A, cpu.operands().decrement_hl())
            .opcode(0x3A)
            .operation(move_operation<byte>)
            .cycles(8)
            .add()
        .operands(cpu.operands().decrement_hl(), cpu.A)
            .opcode(0x32)
            .operation(move_operation<byte>)
            .cycles(8)
            .add()
        .build());

    set.add_instruction(
        instruction_builder(cpu, "ldi")
        .operands(cpu.A, cpu.operands().increment_hl())
            .operation(move_operation<byte>)
            .opcode(0x2A)
            .cycles(8)
            .add()
        .operands(cpu.operands().increment_hl(), cpu.A)
            .operation(move_operation<byte>)
            .opcode(0x22)
            .cycles(8)
            .add()
        .build());

    set.add_instruction(
        instruction_builder(cpu, "ldh")
        .operands(cpu.operands().ff_offset(), cpu.A)
            .operation(move_operation<byte>)
            .opcode(0xE0)
            .cycles(12)
            .add()
        .operands(cpu.A, cpu.operands().ff_offset())
            .operation(move_operation<byte>)
            .opcode(0xF0)
            .cycles(12)
            .add()
        .build());

    set.add_instruction(
        instruction_builder(cpu, "push")
        .operands(cpu.AF).opcode(0xF5).cycles(16).operation(push_operation).add()
        .operands(cpu.BC).opcode(0xC5).cycles(16).operation(push_operation).add()
        .operands(cpu.DE).opcode(0xD5).cycles(16).operation(push_operation).add()
        .operands(cpu.HL).opcode(0xE5).cycles(16).operation(push_operation).add()
        .build());

    set.add_instruction(
        instruction_builder(cpu, "pop")
        .operands(cpu.AF).opcode(0xF1).cycles(12).operation(pop_operation).add()
        .operands(cpu.BC).opcode(0xC1).cycles(12).operation(pop_operation).add()
        .operands(cpu.DE).opcode(0xD1).cycles(12).operation(pop_operation).add()
        .operands(cpu.HL).opcode(0xE1).cycles(12).operation(pop_operation).add()
        .build());
}
