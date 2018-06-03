#include "mem.h"
#include "mem/ld.h"
#include <GameKid/cpu/instruction_set.h>

void ldd_operation(operand<byte>& dst, operand<byte>& src)
{
    dst.store(src.load());
}

void mem::initialize()
{
    _set.add_instruction(std::make_unique<ld_instruction>(_cpu));

    _set.add_instruction(
        instruction_builder(_cpu).name("ldd")
        .operands(_cpu.A, _cpu.operands().decrement_hl()).opcode(0x3A).cycles(8).add()
        .operands(_cpu.operands().decrement_hl(), _cpu.A).opcode(0x32).cycles(8).add()
        .operation<byte>(move_operation<byte>)
        .build());

    _set.add_instruction(
        instruction_builder(_cpu).name("ldi")
        .operands(_cpu.A, _cpu.operands().increment_hl()).opcode(0x2A).cycles(8).add()
        .operands(_cpu.operands().increment_hl(), _cpu.A).opcode(0x22).cycles(8).add()
        .operation<byte>(move_operation<byte>)
        .build());

    _set.add_instruction(
        instruction_builder(_cpu).name("ldh")
        .operands(_cpu.operands().ff_offset(), _cpu.A).opcode(0xE0).cycles(12).add()
        .operands(_cpu.A, _cpu.operands().ff_offset()).opcode(0xF0).cycles(12).add()
        .operation<byte>(move_operation<byte>)
        .build());

    _set.add_instruction(
        instruction_builder(_cpu).name("push")
        .operands(_cpu.AF).opcode(0xF5).cycles(16).add()
        .operands(_cpu.BC).opcode(0xC5).cycles(16).add()
        .operands(_cpu.DE).opcode(0xD5).cycles(16).add()
        .operands(_cpu.HL).opcode(0xE5).cycles(16).add()
        .operation<word>([this](operand<word>& op) { _cpu.push(op.load()); })
        .build());

    _set.add_instruction(
        instruction_builder(_cpu).name("pop")
        .operands(_cpu.AF).opcode(0xF1).cycles(12).add()
        .operands(_cpu.BC).opcode(0xC1).cycles(12).add()
        .operands(_cpu.DE).opcode(0xD1).cycles(12).add()
        .operands(_cpu.HL).opcode(0xE1).cycles(12).add()
        .operation<word>([this](operand<word>& op)
        {
            word value = op.load();
            _cpu.pop(&value);
            op.store(value);
        })
        .build());
}
