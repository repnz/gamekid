#pragma once
#include "instructions/mem/mem_operands.h"

class operands
{
private:
    cpu& _cpu;
    std::vector<reg_mem_operand> _reg_mem_operands;
    std::vector<reg16_with_offset> _reg16_with_offset_operands;
    imm_operand<byte> _immidiate_byte;
    imm_operand<word> _immidiate_word;
    imm_mem_operand<byte> _immidiate_mem_byte;
    imm_mem_operand<word> _immidiate_mem_word;
    c_mem_operand _c_mem;
    std::vector<constant_operand> _constants;
    inc_reg_mem_operand _inc_hl;
    dec_reg_mem_operand _dec_hl;
    ff_offset_mem_operand _ff_offset;
public:
    explicit operands(cpu& cpu);
    operands(const operands&) = delete;
    operands& operator=(operands&) = delete;
    reg_mem_operand & reg_mem(reg16& r);
    reg16_with_offset& reg16_with_offset(reg16& r);
    imm_operand<byte>& immidiate_byte();
    imm_operand<word>& immidiate_word();
    imm_mem_operand<byte>& immidiate_mem_byte();
    imm_mem_operand<word>& immidiate_mem_word();
    c_mem_operand& c_memory();
    inc_reg_mem_operand& increment_hl();
    dec_reg_mem_operand& decrement_hl();
    constant_operand& constant(byte val);
    ff_offset_mem_operand& ff_offset();
};
