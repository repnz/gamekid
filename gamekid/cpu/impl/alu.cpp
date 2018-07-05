#include "alu.h"
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/builders/instruction_builder.h>
#include <gamekid/cpu/opcodes.h>
#include <gamekid/cpu/operands_container.h>

using namespace gamekid::cpu::impl;
using namespace gamekid::cpu::builders;
using namespace gamekid::cpu;

static void base_add_operation(cpu& cpu, operand<byte>& op, bool add_carry){
    byte original_value = cpu.A.load();
    byte new_value = original_value + op.load();

    if (add_carry){
        new_value += cpu.F.carry_bit();
    }

    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.carry(new_value < original_value);
    cpu.F.half_carry(gamekid::utils::bits::check_carry_up(original_value, new_value, 3));
    cpu.A.store(new_value);
}

void alu::add_operation(cpu& cpu, operand<byte>& op){
    base_add_operation(cpu, op, false);
}

void alu::adc_operation(cpu& cpu, operand<byte>& op){
    base_add_operation(cpu, op, true);
}

void base_sub_operation(cpu& cpu, operand<byte>& op, bool sub_carry, bool save_result){
    byte original_value = cpu.A.load();
    byte new_value = original_value - op.load();

    if (sub_carry){
        new_value -= cpu.F.carry_bit();
    }

    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.carry(new_value > original_value);
    cpu.F.half_carry(gamekid::utils::bits::check_carry_down(original_value, new_value, 3));

    if (save_result){
        cpu.A.store(new_value);
    }
}


void alu::sub_operation(cpu& cpu, operand<byte>& op){
    base_sub_operation(cpu, op, false, true);
}

void alu::sbc_operation(cpu& cpu, operand<byte>& op){
    base_sub_operation(cpu, op, true, true);
}

void alu::and_operation(cpu& cpu, operand<byte>& op){
    const byte new_value = cpu.A.load() & op.load();
    cpu.A.store(new_value);
    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.half_carry(true);
    cpu.F.carry(false);
}

void alu::or_operation(cpu& cpu, operand<byte>& op){
    const byte new_value = cpu.A.load() | op.load();
    cpu.A.store(new_value);
    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.half_carry(false);
    cpu.F.carry(false);
}

void alu::xor_operation(cpu& cpu, operand<byte>& op){
    const byte new_value = cpu.A.load() ^ op.load();
    cpu.A.store(new_value);
    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.half_carry(false);
    cpu.F.carry(false);
}

void alu::cp_operation(cpu& cpu, operand<byte>& op){
    base_sub_operation(cpu, op, false, false);
}


void alu::inc_operation(cpu& cpu, operand<byte>& op){
    const byte new_value = op.load() + 1;
    
    cpu.F.half_carry(new_value == 0x10);
    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    // carry flag is not affected.
    op.store(new_value);
}

void alu::dec_operation(cpu& cpu, operand<byte>& op){
    const byte new_value = op.load() - 1;
    cpu.F.half_carry(new_value == 0xF);
    cpu.F.zero(new_value == 0);
    cpu.F.substract(true);
    op.store(new_value);
}

void alu::inc_word_operation(cpu& cpu, operand<word>& op){
    // none of the flags are affected
    op.store(op.load() + 1);
}

void alu::dec_word_operation(cpu& cpu, operand<word>& op){
    // none of the flags are affected
    op.store(op.load() - 1);
}

static void base_add_word_operation(cpu& cpu, operand<word>& op, word value){
    const word original = op.load();
    const word result = original + value;
    op.store(result);

    cpu.F.half_carry(gamekid::utils::bits::check_carry_up(original, result, 11));
    cpu.F.carry(gamekid::utils::bits::check_carry_up(original, result, 15));
    cpu.F.substract(false);
}

void alu::add_to_hl_operation(cpu& cpu, operand<word>& hl, operand<word>& reg){
    base_add_word_operation(cpu, hl, reg.load());
}

void alu::add_to_sp_operation(cpu& cpu, operand<word>& sp, operand<byte>& reg) {
    base_add_word_operation(cpu, sp, reg.load());
    cpu.F.zero(false);
}


void alu::initialize() {
    _set.add_instruction(instruction_builder(_cpu, "add")
        .operands(_cpu.A).opcode(ADD_A).cycles(4).operation(add_operation).add()
        .operands(_cpu.B).opcode(ADD_B).cycles(4).operation(add_operation).add()
        .operands(_cpu.C).opcode(ADD_C).cycles(4).operation(add_operation).add()
        .operands(_cpu.D).opcode(ADD_D).cycles(4).operation(add_operation).add()
        .operands(_cpu.E).opcode(ADD_E).cycles(4).operation(add_operation).add()
        .operands(_cpu.H).opcode(ADD_H).cycles(4).operation(add_operation).add()
        .operands(_cpu.L).opcode(ADD_L).cycles(4).operation(add_operation).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).opcode(ADD_HL_mem).operation(add_operation).cycles(8).add()
        .operands(_cpu.operands().immidiate_byte()).opcode(ADD_IMM).operation(add_operation).cycles(8).add()
        .operands(_cpu.HL, _cpu.BC).opcode(ADD_HL_BC).cycles(8).operation(add_to_hl_operation).add()
        .operands(_cpu.HL, _cpu.DE).opcode(ADD_HL_DE).cycles(8).operation(add_to_hl_operation).add()
        .operands(_cpu.HL, _cpu.HL).opcode(ADD_HL_HL).cycles(8).operation(add_to_hl_operation).add()
        .operands(_cpu.HL, _cpu.SP).opcode(ADD_HL_SP).cycles(8).operation(add_to_hl_operation).add()
        .operands(_cpu.SP, _cpu.operands().immidiate_byte()).opcode(ADD_SP_IMM).cycles(16).operation(add_to_sp_operation).add()
        .build()
    );
    add_alu_instruction("sub", opcodes_struct {
                            SUB_A,
                            SUB_B,
                            SUB_C,
                            SUB_D,
                            SUB_E,
                            SUB_H,
                            SUB_L,
                            SUB_HL_mem,
                            SUB_IMM,
        }, sub_operation);

    add_alu_instruction("sbc", opcodes_struct {
                            SBC_A,
                            SBC_B,
                            SBC_C,
                            SBC_D,
                            SBC_E,
                            SBC_H,
                            SBC_L,
                            SBC_HL_mem,
                            SBC_IMM,
        }, sbc_operation);



    add_alu_instruction("and", opcodes_struct {
                            AND_A,
                            AND_B,
                            AND_C,
                            AND_D,
                            AND_E,
                            AND_H,
                            AND_L,
                            AND_HL_mem,
                            AND_IMM,
        }, and_operation);

    add_alu_instruction("or", opcodes_struct {
                            OR_A,
                            OR_B,
                            OR_C,
                            OR_D,
                            OR_E,
                            OR_H,
                            OR_L,
                            OR_HL_mem,
                            OR_IMM,
        }, or_operation);

    add_alu_instruction("xor", opcodes_struct {
                            XOR_A,
                            XOR_B,
                            XOR_C,
                            XOR_D,
                            XOR_E,
                            XOR_H,
                            XOR_L,
                            XOR_HL_mem,
                            XOR_IMM,
        }, xor_operation);

    add_alu_instruction("cp", opcodes_struct {
                            CP_A,
                            CP_B,
                            CP_C,
                            CP_D,
                            CP_E,
                            CP_H,
                            CP_L,
                            CP_HL_mem,
                            CP_IMM,
        }, cp_operation);


    _set.add_instruction(instruction_builder(_cpu, "inc")
        .operands(_cpu.A).opcode(INC_A).operation(inc_operation).cycles(4).add()
        .operands(_cpu.B).opcode(INC_B).operation(inc_operation).cycles(4).add()
        .operands(_cpu.C).opcode(INC_C).operation(inc_operation).cycles(4).add()
        .operands(_cpu.D).opcode(INC_D).operation(inc_operation).cycles(4).add()
        .operands(_cpu.E).opcode(INC_E).operation(inc_operation).cycles(4).add()
        .operands(_cpu.H).opcode(INC_H).operation(inc_operation).cycles(4).add()
        .operands(_cpu.L).opcode(INC_L).operation(inc_operation).cycles(4).add()
        .operands(_cpu.BC).opcode(INC_BC).operation(inc_word_operation).cycles(8).add()
        .operands(_cpu.DE).opcode(INC_DE).operation(inc_word_operation).cycles(8).add()
        .operands(_cpu.HL).opcode(INC_HL).operation(inc_word_operation).cycles(8).add()
        .operands(_cpu.SP).opcode(INC_SP).operation(inc_word_operation).cycles(8).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).operation(inc_operation).opcode(INC_HL_mem).cycles(12).add()
        .build()
    );

    _set.add_instruction(instruction_builder(_cpu, "dec")
        .operands(_cpu.A).opcode(DEC_A).cycles(4).operation(dec_operation).add()
        .operands(_cpu.B).opcode(DEC_B).cycles(4).operation(dec_operation).add()
        .operands(_cpu.C).opcode(DEC_C).cycles(4).operation(dec_operation).add()
        .operands(_cpu.D).opcode(DEC_D).cycles(4).operation(dec_operation).add()
        .operands(_cpu.E).opcode(DEC_E).cycles(4).operation(dec_operation).add()
        .operands(_cpu.H).opcode(DEC_H).cycles(4).operation(dec_operation).add()
        .operands(_cpu.L).opcode(DEC_L).cycles(4).operation(dec_operation).add()
        .operands(_cpu.BC).opcode(DEC_BC).cycles(4).operation(dec_word_operation).add()
        .operands(_cpu.DE).opcode(DEC_DE).cycles(4).operation(dec_word_operation).add()
        .operands(_cpu.HL).opcode(DEC_HL).cycles(4).operation(dec_word_operation).add()
        .operands(_cpu.SP).opcode(DEC_SP).cycles(4).operation(dec_word_operation).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).opcode(DEC_HL_mem).cycles(12).operation(dec_operation).add()
        .build()
    );


}

void alu::add_alu_instruction(const std::string& name, const opcodes_struct& opcodes,
    cpu_operation<byte> operation){
    _set.add_instruction(instruction_builder(_cpu, name)
        .operands(_cpu.A).opcode(opcodes.A).cycles(4).operation(operation).add()
        .operands(_cpu.B).opcode(opcodes.B).cycles(4).operation(operation).add()
        .operands(_cpu.C).opcode(opcodes.C).cycles(4).operation(operation).add()
        .operands(_cpu.D).opcode(opcodes.D).cycles(4).operation(operation).add()
        .operands(_cpu.E).opcode(opcodes.E).cycles(4).operation(operation).add()
        .operands(_cpu.H).opcode(opcodes.H).cycles(4).operation(operation).add()
        .operands(_cpu.L).opcode(opcodes.L).cycles(4).operation(operation).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).opcode(opcodes.HL_mem).operation(operation).cycles(8).add()
        .operands(_cpu.operands().immidiate_byte()).opcode(opcodes.IMM).operation(operation).cycles(8).add()
        .build()
    );
}
