#include "operands.h"

operands::operands(cpu& cpu) : 
_cpu(cpu),
_immidiate_byte(cpu),
_immidiate_word(cpu),
_immidiate_mem_byte(cpu),
_immidiate_mem_word(cpu),
_c_mem(cpu),
_inc_hl(cpu.mem, cpu.HL),
_dec_hl(cpu.mem, cpu.HL),
_ff_offset(cpu),
_nz(cpu.F, flags_reg8::ZERO, "nz", false),
_z(cpu.F, flags_reg8::ZERO, "z", true),
_nc(cpu.F, flags_reg8::CARRY, "nc", false),
_c(cpu.F, flags_reg8::CARRY, "c", true),
_hl_addressing(cpu.HL)
{
}

c_mem_operand& operands::c_memory()
{
    return _c_mem;
}

inc_reg_mem_operand& operands::increment_hl()
{
    return _inc_hl;
}

dec_reg_mem_operand& operands::decrement_hl()
{
    return _dec_hl;
}

constant_operand& operands::constant(byte val)
{
    for (constant_operand& op : _constants)
    {
        if (op.value == val)
        {
            return op;
        }
    }
    _constants.push_back(constant_operand(val));
    return _constants.back();
}

ff_offset_mem_operand& operands::ff_offset()
{
    return _ff_offset;
}

cc_operand& operands::nz()
{
    return _nz;
}

cc_operand& operands::z()
{
    return _z;
}

cc_operand& operands::nc()
{
    return _nc;
}

cc_operand& operands::c()
{
    return _c;
}

reg16_addressing& operands::hl_addressing()
{
    return _hl_addressing;
}

reg_mem_operand& operands::reg_mem(reg16& r)
{
    for (auto& offset : _reg_mem_operands)
    {
        if (offset.reg().name() == r.name())
        {
            return offset;
        }
    }

    _reg_mem_operands.push_back(reg_mem_operand(_cpu.mem, r));
    return _reg_mem_operands.back();
}

reg16_with_offset& operands::reg16_with_offset(reg16& r)
{
    for (auto& offset : _reg16_with_offset_operands)
    {
        if (offset.reg().name() == r.name())
        {
            return offset;
        }
    }

    _reg16_with_offset_operands.push_back(reg16_with_offset(r));
    return _reg16_with_offset_operands.back();
}

imm_operand<byte>& operands::immidiate_byte()
{
    return _immidiate_byte;
}

imm_mem_operand<byte>& operands::immidiate_mem_byte()
{
    return _immidiate_mem_byte;
}

imm_mem_operand<word>& operands::immidiate_mem_word()
{
    return _immidiate_mem_word;
}

imm_operand<word>& operands::immidiate_word()
{
    return _immidiate_word;
}





