#pragma once
#include "GameKid/cpu/instruction.h"
#include "move_opcode.h"
#include "mem_operands.h"

class ld_instruction : public instruction
{
private:
    // Operands
    c_mem_operand _c_mem;
    imm_mem_operand<byte> _imm_mem_byte;
    imm_mem_operand<word> _imm_mem_word;
    reg_mem_operand _hl_mem;

    // Opcodes
    std::vector<move_opcode<byte>> _imm_to_reg;
    std::vector<move_opcode<byte>>  _reg_to_reg;
    std::vector<move_opcode<byte>> _reg_to_mem;
    std::vector<move_opcode<byte>> _mem_to_reg;
    move_opcode<byte> _a_to_c_mem;
    move_opcode<byte> _c_mem_to_a;
    move_opcode<byte> _a_to_imm_mem;
    move_opcode<byte> _imm_to_hl;
    move_opcode<byte> _imm_mem_to_a;
    std::vector<move_opcode<word>> _imm16_to_reg16;
    move_opcode<word> _sp_to_imm_mem;
    move_opcode<word> _hl_to_sp;
    move_opcode<word> _sp_offset_to_hl;
  
public:
    explicit ld_instruction(cpu& cpu)
        : instruction(cpu, "ld"), 
    _c_mem(cpu),
    _imm_mem_byte(cpu),
    _imm_mem_word(cpu),
    _hl_mem(cpu.mem, cpu.HL),
    _a_to_c_mem("ld", cpu, 0xE2, 8, cpu.A, _c_mem), 
    _c_mem_to_a("ld", cpu, 0xF2, 8, c_mem_operand(cpu), cpu.A),
    _a_to_imm_mem("ld", cpu, 0xEA, 16, cpu.A, _imm_mem_byte),
    _imm_to_hl("ld", cpu, 0x36, 12, imm_operand<byte>(cpu), _hl_mem),
    _imm_mem_to_a("ld", cpu, 0xFA, 16, imm_mem_operand<byte>(cpu), cpu.A),
    _sp_to_imm_mem("ld", cpu, 0x08, 20, cpu.SP, _imm_mem_word),
    _hl_to_sp("ld", cpu, 0xF9, 8, cpu.HL, cpu.SP),
    _sp_offset_to_hl("ld", cpu, 0xf8, 12, reg16_with_offset(cpu, cpu.SP), cpu.HL)
    {
        add_imm_to_reg(0x3E, cpu.A);
        add_imm_to_reg(0x06, cpu.B);
        add_imm_to_reg(0x0E, cpu.C);
        add_imm_to_reg(0x16, cpu.D);
        add_imm_to_reg(0x1E, cpu.E);
        add_imm_to_reg(0x26, cpu.H);
        add_imm_to_reg(0x2E, cpu.L);

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

        opcodes.push_back(&_a_to_c_mem);
        opcodes.push_back(&_a_to_imm_mem);
        opcodes.push_back(&_imm_to_hl);
        opcodes.push_back(&_imm_mem_to_a);
        opcodes.push_back(&_c_mem_to_a);
        opcodes.push_back(&_sp_to_imm_mem);
        opcodes.push_back(&_sp_offset_to_hl);
    }

    void reg_to_imm(byte* reg_address)
    {
        *reg_address = _cpu.mem.load_byte(_cpu.PC + 1);
    }

    void add_imm_to_reg(byte op_value, reg8& reg)
    {
        _imm_to_reg.push_back(
            move_opcode<byte>("ld", _cpu, op_value, 8, imm_operand<byte>(_cpu), reg)
        );

        opcodes.push_back(&_imm_to_reg.back());
    }

    void add_reg_to_reg_opcodes(byte b_value, reg8& dst)
    {
        add_reg_to_reg(b_value - 7, _cpu.A, dst);
        add_reg_to_reg(b_value + 0, _cpu.B, dst);
        add_reg_to_reg(b_value + 1, _cpu.C, dst);
        add_reg_to_reg(b_value + 2, _cpu.D, dst);
        add_reg_to_reg(b_value + 3, _cpu.E, dst);
        add_reg_to_reg(b_value + 4, _cpu.H, dst);
        add_reg_to_reg(b_value + 5, _cpu.L, dst);
    }

    void add_reg_to_reg(byte val, const reg8& src, reg8& dst)
    {
        _reg_to_reg.push_back(move_opcode<byte>("ld", _cpu, val, 4, src, dst));
        opcodes.push_back(&_reg_to_reg.back());
    }

    void add_reg_to_mem(byte val, const reg8& src, reg16& dst)
    {
        reg_mem_operand dst_operand(_cpu.mem, dst);

        _reg_to_mem.push_back(
            move_opcode<byte>("ld", _cpu, val, 8, src, dst_operand)
        );

        opcodes.push_back(&_reg_to_mem.back());
    }

    void add_mem_to_reg(byte val, reg16& src, reg8& dst)
    {
        reg_mem_operand src_operand(_cpu.mem, src);
        
        _mem_to_reg.push_back(
            move_opcode<byte>("ld", _cpu, val, 8, src_operand, dst)
        );

        opcodes.push_back(&_mem_to_reg.back());
    }

    void add_imm16_to_reg16(byte val, reg16& reg)
    {
        _imm16_to_reg16.push_back(
            move_opcode<word>("ld", _cpu, val, 12, imm_operand<word>(_cpu), reg)
        );

        opcodes.push_back(&_imm16_to_reg16.back());
    }

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        // leave parsing for later
        return {};
    }
};
