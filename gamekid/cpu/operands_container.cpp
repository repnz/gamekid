#include "operands_container.h"
#include "operands/flags_reg8.h"
#include <gamekid/system.h>

using gamekid::cpu::operands_container;
using namespace gamekid::cpu::operands;

operands_container::operands_container(gamekid::system& sys) :
_system(sys),
_immidiate_byte(sys),
_immidiate_word(sys),
_immidiate_mem_byte(sys),
_immidiate_mem_word(sys),
_c_mem(sys),
_inc_hl(sys.memory(), sys.cpu().HL),
_dec_hl(sys.memory(), sys.cpu().HL),
_ff_offset(sys),
_nz(sys.cpu().F, operands::flags_reg8::ZERO, "nz", false),
_z(sys.cpu().F, flags_reg8::ZERO, "z", true),
_nc(sys.cpu().F, flags_reg8::CARRY, "nc", false),
_c(sys.cpu().F, flags_reg8::CARRY, "c", true),
_hl_addressing(sys.cpu().HL){
    _constants.reserve(20);
    _reg16_with_offset_operands.reserve(20);
    _reg_mem_operands.reserve(20);
}

c_mem_operand& operands_container::c_memory(){
    return _c_mem;
}

inc_reg_mem_operand& operands_container::increment_hl(){
    return _inc_hl;
}

dec_reg_mem_operand& operands_container::decrement_hl(){
    return _dec_hl;
}

constant_operand& operands_container::constant(byte val){
    for (constant_operand& op : _constants) {
        if (op.value == val) {
            return op;
        }
    }
    _constants.emplace_back(val);
    constant_operand& op =  _constants.back();
    return op;
}

ff_offset_mem_operand& operands_container::ff_offset(){
    return _ff_offset;
}

cc_operand& operands_container::nz(){
    return _nz;
}

cc_operand& operands_container::z(){
    return _z;
}

cc_operand& operands_container::nc(){
    return _nc;
}

cc_operand& operands_container::c(){
    return _c;
}

reg16_addressing& operands_container::hl_addressing(){
    return _hl_addressing;
}

reg_mem_operand& operands_container::reg_mem(reg16& r){
    for (auto& offset : _reg_mem_operands){
        if (offset.reg().name() == r.name()){
            return offset;
        }
    }
    return _reg_mem_operands.emplace_back(_system.memory(), r);
}

reg16_with_offset& operands_container::reg16_with_offset(reg16& r){
    for (auto& offset : _reg16_with_offset_operands){
        if (offset.reg().name() == r.name()){
            return offset;
        }
    }

    _reg16_with_offset_operands.emplace_back(_system, r);
    return _reg16_with_offset_operands.back();
}

imm_operand<byte>& operands_container::immidiate_byte(){
    return _immidiate_byte;
}

imm_mem_operand<byte>& operands_container::immidiate_mem_byte(){
    return _immidiate_mem_byte;
}

imm_mem_operand<word>& operands_container::immidiate_mem_word(){
    return _immidiate_mem_word;
}

imm_operand<word>& operands_container::immidiate_word(){
    return _immidiate_word;
}