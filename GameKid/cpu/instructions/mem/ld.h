#pragma once
#include "GameKid/cpu/instruction.h"
#include "GameKid/cpu/base_opcodes/register_opcode.h"

class reg_to_reg_opcode : opcode
{
private:
    reg src;
    reg dst;
public:
    reg_to_reg_opcode(cpu& cpu, const std::string& name, byte value, const reg& src, const reg& dst, byte cycles) 
        : opcode(cpu, name, value, false, cycles), src(src), dst(dst)
    {
    }
    
    void run() override
    {
        *dst.address = *src.address;
    }
    
    std::string to_str(byte* next) override
    {
        return name + " " + dst.name + ", " + src.name;
    }
};

class ld_instruction : instruction
{
private:
    std::vector<register_opcode> _imm_to_reg;
    std::vector<reg_to_reg_opcode> _reg_to_reg;

public:
    ld_instruction(cpu& cpu, const std::string& name)
        : instruction(cpu, name)
    {
        add_imm_to_reg(0x3E, cpu.regs.A);
        add_imm_to_reg(0x06, cpu.regs.B);
        add_imm_to_reg(0x0E, cpu.regs.C);
        add_imm_to_reg(0x16, cpu.regs.D);
        add_imm_to_reg(0x1E, cpu.regs.E);
        add_imm_to_reg(0x26, cpu.regs.H);
        add_imm_to_reg(0x2E, cpu.regs.L);
        
        add_reg_opcodes(0x78, cpu.regs.A);
        add_reg_opcodes(0x40, cpu.regs.B);
        add_reg_opcodes(0x48, cpu.regs.C);
        add_reg_opcodes(0x50, cpu.regs.D);
        add_reg_opcodes(0x58, cpu.regs.E);
        add_reg_opcodes(0x60, cpu.regs.H);
        add_reg_opcodes(0x68, cpu.regs.L);
    }

    void reg_to_imm(byte* reg_address)
    {
        *reg_address = _cpu.mem.load_byte(_cpu.PC + 1);
    }

    void add_imm_to_reg(byte op_value, const reg& reg)
    {
        _imm_to_reg.push_back(register_opcode(
            _cpu,
            "ld",
            op_value,
            [this](byte* b) {reg_to_imm(b); },
            reg,
            false,
            8
        ));
    }

    void add_reg_opcodes(byte b_value, const reg& dst)
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

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        // leave parsing for later
        return {};
    }
};
