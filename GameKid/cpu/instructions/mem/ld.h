#pragma once
#include "GameKid/cpu/instruction.h"
#include "move_opcode.h"
#include "operand.h"

class ld_instruction : public instruction
{
private:
    std::vector<move_opcode<imm_operand<byte>, reg8_operand>> _imm_to_reg;
    std::vector<move_opcode<reg8_operand, reg8_operand>> _reg_to_reg;
    std::vector<move_opcode<reg8_operand, reg_mem_operand>> _reg_to_mem;
    std::vector<move_opcode<reg_mem_operand, reg8_operand>> _mem_to_reg;
    move_opcode<reg8_operand, c_mem_operand> _a_to_c_mem;
    move_opcode<c_mem_operand, reg8_operand> _c_mem_to_a;
    move_opcode<reg8_operand, imm_mem_operand> _a_to_imm_mem;
    move_opcode<imm_operand<byte>, reg_mem_operand> _imm_to_hl;
    move_opcode<imm_mem_operand, reg8_operand> _imm_mem_to_a;
    
public:
    explicit ld_instruction(cpu& cpu)
        : instruction(cpu, "ld"), 
    _a_to_c_mem(cpu, 0xE2, 8, reg8_operand(cpu.regs.A), c_mem_operand(cpu)), 
    _c_mem_to_a(cpu, 0xF2, 8, c_mem_operand(cpu), reg8_operand(cpu.regs.A)),
    _a_to_imm_mem(cpu, 0xEA, 16, reg8_operand(cpu.regs.A), imm_mem_operand(cpu)),
    _imm_to_hl(cpu, 0x36, 12, imm_operand<byte>(cpu), reg_mem_operand(cpu.mem, cpu.regs.HL)),
    _imm_mem_to_a(cpu, 0xFA, 16, imm_mem_operand(cpu), cpu.regs.A)
    {
        add_imm_to_reg(0x3E, cpu.regs.A);
        add_imm_to_reg(0x06, cpu.regs.B);
        add_imm_to_reg(0x0E, cpu.regs.C);
        add_imm_to_reg(0x16, cpu.regs.D);
        add_imm_to_reg(0x1E, cpu.regs.E);
        add_imm_to_reg(0x26, cpu.regs.H);
        add_imm_to_reg(0x2E, cpu.regs.L);

        add_reg_to_reg_opcodes(0x78, cpu.regs.A);
        add_reg_to_reg_opcodes(0x40, cpu.regs.B);
        add_reg_to_reg_opcodes(0x48, cpu.regs.C);
        add_reg_to_reg_opcodes(0x50, cpu.regs.D);
        add_reg_to_reg_opcodes(0x58, cpu.regs.E);
        add_reg_to_reg_opcodes(0x60, cpu.regs.H);
        add_reg_to_reg_opcodes(0x68, cpu.regs.L);

        // Move from Register To Memory

        add_reg_to_mem(0x77, cpu.regs.A, cpu.regs.HL);
        add_reg_to_mem(0x70, cpu.regs.B, cpu.regs.HL);
        add_reg_to_mem(0x71, cpu.regs.C, cpu.regs.HL);
        add_reg_to_mem(0x72, cpu.regs.D, cpu.regs.HL);
        add_reg_to_mem(0x73, cpu.regs.E, cpu.regs.HL);
        add_reg_to_mem(0x74, cpu.regs.H, cpu.regs.HL);
        add_reg_to_mem(0x75, cpu.regs.L, cpu.regs.HL);


        // Move A Register to BC, DE
        add_reg_to_mem(0x02, cpu.regs.A, cpu.regs.BC);
        add_reg_to_mem(0x12, cpu.regs.A, cpu.regs.DE);

        // Move from Register To Memory

        add_mem_to_reg(0x7E, cpu.regs.HL, cpu.regs.A);
        add_mem_to_reg(0x0A, cpu.regs.BC, cpu.regs.A);
        add_mem_to_reg(0x1A, cpu.regs.DE, cpu.regs.A);

        add_mem_to_reg(0x46, cpu.regs.HL, cpu.regs.B);
        add_mem_to_reg(0x4E, cpu.regs.HL, cpu.regs.C);
        add_mem_to_reg(0x56, cpu.regs.HL, cpu.regs.D);
        add_mem_to_reg(0x5E, cpu.regs.HL, cpu.regs.E);
        add_mem_to_reg(0x66, cpu.regs.HL, cpu.regs.H);
        add_mem_to_reg(0x6E, cpu.regs.HL, cpu.regs.L);
        

        opcodes.push_back(&_a_to_c_mem);
        opcodes.push_back(&_a_to_imm_mem);
        opcodes.push_back(&_imm_to_hl);
        opcodes.push_back(&_imm_mem_to_a);
        opcodes.push_back(&_c_mem_to_a);
    }

    void reg_to_imm(byte* reg_address)
    {
        *reg_address = _cpu.mem.load_byte(_cpu.PC + 1);
    }

    void add_imm_to_reg(byte op_value, const reg8& reg)
    {
        _imm_to_reg.push_back(
            move_opcode<imm_operand<byte>, reg8_operand>(_cpu, op_value, 8, imm_operand<byte>(_cpu), reg)
        );

        opcodes.push_back(&_imm_to_reg.back());
    }

    void add_reg_to_reg_opcodes(byte b_value, const reg8& dst)
    {
        add_reg_to_reg(b_value - 7, _cpu.regs.A, dst);
        add_reg_to_reg(b_value + 0, _cpu.regs.B, dst);
        add_reg_to_reg(b_value + 1, _cpu.regs.C, dst);
        add_reg_to_reg(b_value + 2, _cpu.regs.D, dst);
        add_reg_to_reg(b_value + 3, _cpu.regs.E, dst);
        add_reg_to_reg(b_value + 4, _cpu.regs.H, dst);
        add_reg_to_reg(b_value + 5, _cpu.regs.L, dst);
    }

    void add_reg_to_reg(byte val, const reg8& src, const reg8& dst)
    {
        _reg_to_reg.push_back(move_opcode<reg8_operand, reg8_operand>(_cpu, val, 4, src, dst));
        opcodes.push_back(&_reg_to_reg.back());
    }

    void add_reg_to_mem(byte val, const reg8& src, const reg16& dst)
    {
        reg8_operand src_operand(src);
        reg_mem_operand dst_operand(_cpu.mem, dst);

        _reg_to_mem.push_back(
            move_opcode<reg8_operand, reg_mem_operand>(_cpu, val, 8, src_operand, dst_operand)
        );

        opcodes.push_back(&_reg_to_mem.back());
    }

    void add_mem_to_reg(byte val, const reg16& src, const reg8& dst)
    {
        reg_mem_operand src_operand(_cpu.mem, src);
        reg8_operand dst_operand(dst);
        
        _mem_to_reg.push_back(
            move_opcode<reg_mem_operand, reg8_operand>(_cpu, val, 8, src_operand, dst_operand)
        );

        opcodes.push_back(&_mem_to_reg.back());
    }


    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        // leave parsing for later
        return {};
    }
};
