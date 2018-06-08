#include "mem.h"
#include "mem/ld.h"
#include <GameKid/cpu/instruction_set.h>

void ldd_operation(cpu& cpu, operand<byte>& dst, operand<byte>& src)
{
    dst.store(src.load());
}

void push_operation(cpu& cpu, operand<word>& dst)
{
    cpu.push(dst.load());
}

void pop_operation(cpu& cpu, operand<word>& dst)
{
    dst.store(cpu.pop());

}

void mem::initialize()
{
    _set.add_instruction(std::make_unique<ld_instruction>(_cpu));

    _set.add_instruction(
        instruction_builder(_cpu, "ldd")
        .operands(_cpu.A, _cpu.operands().decrement_hl()).opcode(0x3A).operation(move_operation<byte>).cycles(8).add()
        .operands(_cpu.operands().decrement_hl(), _cpu.A).opcode(0x32).operation(move_operation<byte>).cycles(8).add()
        .build());

    _set.add_instruction(
        instruction_builder(_cpu, "ldi")
        .operands(_cpu.A, _cpu.operands().increment_hl()).operation(move_operation<byte>).opcode(0x2A).cycles(8).add()
        .operands(_cpu.operands().increment_hl(), _cpu.A).operation(move_operation<byte>).opcode(0x22).cycles(8).add()
        .build());

    _set.add_instruction(
        instruction_builder(_cpu, "ldh")
        .operands(_cpu.operands().ff_offset(), _cpu.A).operation(move_operation<byte>).opcode(0xE0).cycles(12).add()
        .operands(_cpu.A, _cpu.operands().ff_offset()).operation(move_operation<byte>).opcode(0xF0).cycles(12).add()
        .build());

    _set.add_instruction(
        instruction_builder(_cpu, "push")
        .operands(_cpu.AF).opcode(0xF5).cycles(16).operation(push_operation).add()
        .operands(_cpu.BC).opcode(0xC5).cycles(16).operation(push_operation).add()
        .operands(_cpu.DE).opcode(0xD5).cycles(16).operation(push_operation).add()
        .operands(_cpu.HL).opcode(0xE5).cycles(16).operation(push_operation).add()
        .build());

    _set.add_instruction(
        instruction_builder(_cpu, "pop")
        .operands(_cpu.AF).opcode(0xF1).cycles(12).operation(pop_operation).add()
        .operands(_cpu.BC).opcode(0xC1).cycles(12).operation(pop_operation).add()
        .operands(_cpu.DE).opcode(0xD1).cycles(12).operation(pop_operation).add()
        .operands(_cpu.HL).opcode(0xE1).cycles(12).operation(pop_operation).add()
        .build());
}
