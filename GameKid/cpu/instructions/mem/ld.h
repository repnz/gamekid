#pragma once
#include "GameKid/cpu/instruction.h"
#include "opcodes/imm_to_reg_opcode.h"
#include "opcodes/reg_to_reg_opcode.h"
#include "opcodes/reg_to_hl_opcode.h"

class ld_instruction : public instruction
{
private:
    std::vector<imm_to_reg_opcode> _imm_to_reg;
    std::vector<reg_to_reg_opcode> _reg_to_reg;
    std::vector<reg_to_hl_opcode> _reg_to_hl;

public:
    explicit ld_instruction(cpu& cpu)
        : instruction(cpu, "ld")
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

        add_reg_to_hl(0x77, cpu.regs.A);
        add_reg_to_hl(0x70, cpu.regs.B);
        add_reg_to_hl(0x71, cpu.regs.C);
        add_reg_to_hl(0x72, cpu.regs.D);
        add_reg_to_hl(0x73, cpu.regs.E);
        add_reg_to_hl(0x74, cpu.regs.H);
        add_reg_to_hl(0x75, cpu.regs.L);

    }

    void reg_to_imm(byte* reg_address)
    {
        *reg_address = _cpu.mem.load_byte(_cpu.PC + 1);
    }

    void add_imm_to_reg(byte op_value, const reg& reg)
    {
        _imm_to_reg.push_back(imm_to_reg_opcode(_cpu, reg, op_value));
    }

    void add_reg_to_reg_opcodes(byte b_value, const reg& dst)
    {
        add_reg_to_reg(b_value-7, _cpu.regs.A, dst);
        add_reg_to_reg(b_value+0, _cpu.regs.B, dst);
        add_reg_to_reg(b_value+1, _cpu.regs.C, dst);
        add_reg_to_reg(b_value+2, _cpu.regs.D, dst);
        add_reg_to_reg(b_value+3, _cpu.regs.E, dst);
        add_reg_to_reg(b_value+4, _cpu.regs.H, dst);
        add_reg_to_reg(b_value+5, _cpu.regs.L, dst);
    }

    void add_reg_to_reg(byte val, const reg& src, const reg& dst)
    {
        _reg_to_reg.push_back(reg_to_reg_opcode(_cpu, name, val, src, dst, 4));
    }

    void add_reg_to_hl(byte val, const reg& src)
    {
        _reg_to_hl.push_back(reg_to_hl_opcode(_cpu, src, val));
    }


    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        // leave parsing for later
        return {};
    }
};
