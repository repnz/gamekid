#pragma once
#include "cpu.h"
#include "operands/cc_operand.h"
#include "operands/constant_operand.h"
#include "operands/reg16_addressing.h"
#include "operands/reg_mem_operand.h"
#include "operands/reg16_with_offset.h"
#include "operands/imm_operand.h"
#include "operands/imm_mem_operand.h"
#include "operands/c_mem_operand.h"
#include "operands/ff_offset_mem_operand.h"
#include "operands/op_reg_mem_operand.h"
#include <gamekid/system.h>

namespace gamekid { class system; }

namespace gamekid::cpu {
    class operands_container {
    private:
        system & _system;
        std::vector<operands::reg_mem_operand> _reg_mem_operands;
        std::vector<operands::reg16_with_offset> _reg16_with_offset_operands;
        operands::imm_operand<byte> _immidiate_byte;
        operands::imm_operand<word> _immidiate_word;
        operands::imm_mem_operand<byte> _immidiate_mem_byte;
        operands::imm_mem_operand<word> _immidiate_mem_word;
        operands::c_mem_operand _c_mem;
        std::vector<operands::constant_operand> _constants;
        operands::inc_reg_mem_operand _inc_hl;
        operands::dec_reg_mem_operand _dec_hl;
        operands::ff_offset_mem_operand _ff_offset;
        operands::cc_operand _nz;
        operands::cc_operand _z;
        operands::cc_operand _nc;
        operands::cc_operand _c;
        operands::reg16_addressing _hl_addressing;
    public:
        explicit operands_container(system& cpu);
        operands_container(const operands_container&) = delete;
        operands_container& operator=(operands_container&) = delete;
        operands::reg_mem_operand & reg_mem(operands::reg16& r);
        operands::reg16_with_offset& reg16_with_offset(operands::reg16& r);
        operands::imm_operand<byte>& immidiate_byte();
        operands::imm_operand<word>& immidiate_word();
        operands::imm_mem_operand<byte>& immidiate_mem_byte();
        operands::imm_mem_operand<word>& immidiate_mem_word();
        operands::c_mem_operand& c_memory();
        operands::inc_reg_mem_operand& increment_hl();
        operands::dec_reg_mem_operand& decrement_hl();
        operands::constant_operand& constant(byte val);
        operands::ff_offset_mem_operand& ff_offset();
        operands::cc_operand& nz();
        operands::cc_operand& z();
        operands::cc_operand& nc();
        operands::cc_operand& c();
        operands::reg16_addressing& hl_addressing();
    };

}