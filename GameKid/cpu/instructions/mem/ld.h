#pragma once
#include "GameKid/cpu/instruction.h"
#include "mem_operands.h"
#include "GameKid/cpu/operands.h"
#include <GameKid/cpu/builders/opcode_builder.h>

template <typename T>
void move_operation(cpu& cpu, operand<T>& dst, operand<T>& src)
{
    dst.store(src.load());
}

class ld_instruction : public instruction
{
public:
    explicit ld_instruction(cpu& cpu)
        : instruction(cpu, "ld")
    {
        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(0xE2)
            .operands(cpu.operands().c_memory(), cpu.A)
            .cycles(8)
            .operation(move_operation<byte>)
            .build());

        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(0xF2)
            .operands(cpu.A, cpu.operands().c_memory())
            .cycles(8)
            .operation(move_operation<byte>)
            .build());


        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(0xEA)
            .operands(_cpu.operands().immidiate_mem_byte(), cpu.A)
            .cycles(16)
            .operation(move_operation<byte>)
            .build());

        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(0x36)
            .operands(cpu.A, _cpu.operands().immidiate_byte())
            .cycles(12)
            .operation(move_operation<byte>)
            .build());

        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(0xFA)
            .operands(cpu.A, _cpu.operands().immidiate_mem_byte())
            .cycles(16)
            .operation(move_operation<byte>)
            .build());

        add_imm_to_reg(0x3E, cpu.A);
        add_imm_to_reg(0x06, cpu.B);
        add_imm_to_reg(0x0E, cpu.C);
        add_imm_to_reg(0x16, cpu.D);
        add_imm_to_reg(0x1E, cpu.E);
        add_imm_to_reg(0x26, cpu.H);
        add_imm_to_reg(0x2E, cpu.L);

        // Move from Register to Register

        add_reg_to_reg_opcodes(0x78, cpu.A);
        add_reg_to_reg_opcodes(0x40, cpu.B);
        add_reg_to_reg_opcodes(0x48, cpu.C);
        add_reg_to_reg_opcodes(0x50, cpu.D);
        add_reg_to_reg_opcodes(0x58, cpu.E);
        add_reg_to_reg_opcodes(0x60, cpu.H);
        add_reg_to_reg_opcodes(0x68, cpu.L);

        // Move from Register To Memory

        add_reg_to_mem(0x77, cpu.A, cpu.HL);
        add_reg_to_mem(0x70, cpu.B, cpu.HL);
        add_reg_to_mem(0x71, cpu.C, cpu.HL);
        add_reg_to_mem(0x72, cpu.D, cpu.HL);
        add_reg_to_mem(0x73, cpu.E, cpu.HL);
        add_reg_to_mem(0x74, cpu.H, cpu.HL);
        add_reg_to_mem(0x75, cpu.L, cpu.HL);


        // Move A Register to BC, DE
        add_reg_to_mem(0x02, cpu.A, cpu.BC);
        add_reg_to_mem(0x12, cpu.A, cpu.DE);

        // Move from Register To Memory

        add_mem_to_reg(0x7E, cpu.HL, cpu.A);
        add_mem_to_reg(0x0A, cpu.BC, cpu.A);
        add_mem_to_reg(0x1A, cpu.DE, cpu.A);

        add_mem_to_reg(0x46, cpu.HL, cpu.B);
        add_mem_to_reg(0x4E, cpu.HL, cpu.C);
        add_mem_to_reg(0x56, cpu.HL, cpu.D);
        add_mem_to_reg(0x5E, cpu.HL, cpu.E);
        add_mem_to_reg(0x66, cpu.HL, cpu.H);
        add_mem_to_reg(0x6E, cpu.HL, cpu.L);
        
        // 16 Bit Move From Immidiate To Register
        add_imm16_to_reg16(0x01, cpu.BC);
        add_imm16_to_reg16(0x11, cpu.DE);
        add_imm16_to_reg16(0x21, cpu.HL);
        add_imm16_to_reg16(0x31, cpu.SP);

        add_opcode(opcode_builder<word, word>(_cpu)
            .name("ld")
            .opcode(0xF9)
            .operands(cpu.SP, cpu.HL)
            .cycles(8)
            .operation(move_operation<word>)
            .build());

        add_opcode(opcode_builder<word, word>(_cpu)
            .name("ld")
            .opcode(0xf8)
            .operands(cpu.HL, cpu.operands().reg16_with_offset(cpu.SP))
            .cycles(12)
            .operation(move_operation<word>)
            .build());

        add_opcode(opcode_builder<word, word>(_cpu)
            .name("ld")
            .opcode(0x08)
            .operands(_cpu.operands().immidiate_mem_word(), _cpu.SP)
            .cycles(20)
            .operation(move_operation<word>)
            .build());
    }

    void reg_to_imm(byte* reg_address)
    {
        *reg_address = _cpu.mem.load_byte(_cpu.PC + 1);
    }

    void add_imm_to_reg(byte op_value, reg8& reg)
    {
        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(op_value)
            .operands(reg, _cpu.operands().immidiate_byte())
            .cycles(8)
            .operation(move_operation<byte>)
            .build());
    }

    void add_reg_to_reg_opcodes(byte b_value, reg8& dst)
    {
        add_reg_to_reg(b_value + 7, _cpu.A, dst);
        add_reg_to_reg(b_value + 0, _cpu.B, dst);
        add_reg_to_reg(b_value + 1, _cpu.C, dst);
        add_reg_to_reg(b_value + 2, _cpu.D, dst);
        add_reg_to_reg(b_value + 3, _cpu.E, dst);
        add_reg_to_reg(b_value + 4, _cpu.H, dst);
        add_reg_to_reg(b_value + 5, _cpu.L, dst);
    }

    void add_reg_to_reg(byte val, reg8& src, reg8& dst)
    {
        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(val)
            .operands(dst, src)
            .cycles(4)
            .operation(move_operation<byte>)
            .build());
    }

    void add_reg_to_mem(byte val, reg8& src, reg16& dst)
    {
        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(val)
            .operands(_cpu.operands().reg_mem(dst), src)
            .cycles(8)
            .operation(move_operation<byte>)
            .build());
    }

    void add_mem_to_reg(byte val, reg16& src, reg8& dst)
    {
        add_opcode(opcode_builder<byte, byte>(_cpu)
            .name("ld")
            .opcode(val)
            .operands(dst, _cpu.operands().reg_mem(src))
            .cycles(8)
            .operation(move_operation<byte>)
            .build());
    }

    void add_imm16_to_reg16(byte val, reg16& reg)
    {
        add_opcode(opcode_builder<word, word>(_cpu)
            .name("ld")
            .opcode(val)
            .operands(reg, _cpu.operands().immidiate_word())
            .cycles(12)
            .operation(move_operation<word>)
            .build());
    }
};
