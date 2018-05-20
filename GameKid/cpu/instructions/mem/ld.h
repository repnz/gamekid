#pragma once
#include "GameKid/cpu/instruction.h"
#include "GameKid/cpu/base_opcodes/register_opcode.h"

class ld_instruction : instruction
{
private:
    std::vector<register_opcode> _imm_to_reg;
    std::vector<register_opcode> _reg_to_reg;

public:
    ld_instruction(cpu& cpu, const std::string& name)
        : instruction(cpu, name)
    {
        add_imm_to_reg(0x3E, &cpu.A, "A");
        add_imm_to_reg(0x06, &cpu.B, "B");
        add_imm_to_reg(0x0E, &cpu.C, "C");
        add_imm_to_reg(0x16, &cpu.D, "D");
        add_imm_to_reg(0x1E, &cpu.E, "E");
        add_imm_to_reg(0x26, &cpu.H, "H");
        add_imm_to_reg(0x2E, &cpu.L, "L");
    }

    void reg_to_imm(byte* reg_address)
    {
        *reg_address = _cpu.mem.load_byte(_cpu.PC + 1);
    }

    void add_imm_to_reg(byte op_value, byte* reg_address, std::string reg_name)
    {
        _imm_to_reg.push_back(register_opcode(
            _cpu,
            "ld",
            op_value,
            [this](byte* b) {reg_to_imm(b); },
            reg_name,
            reg_address,
            false,
            8
        ));
    }

    std::vector<byte> parse(const std::vector<std::string>& operands) override
    {
        // leave parsing for later
        return {};
    }
};
