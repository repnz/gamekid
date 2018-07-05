#include "bitmask.h"
#include <gamekid/cpu/builders/instruction_builder.h>
#include <gamekid/cpu/operands_container.h>
#include "gamekid/cpu/opcodes.h"
#include "gamekid/cpu/instruction_set.h"

using namespace gamekid::cpu;
using namespace gamekid::cpu::impl;
using namespace gamekid::utils;

void bitmask::bit_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_check){
    const bool is_on = bits::check_bit(byte_to_check.load(), bit.load());
    cpu.F.zero(!is_on);
    cpu.F.substract(false);
    cpu.F.half_carry(true);
}

void bitmask::res_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change){
    // Flags are not affected.
    const byte new_value = bits::set_bit_off(byte_to_change.load(), bit.load());
    byte_to_change.store(new_value);
}

void bitmask::set_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change){
    // Flags are not affected.
    const byte new_value = bits::set_bit_on(byte_to_change.load(), bit.load());
    byte_to_change.store(new_value);
}


void bitmask::build_register_opcodes(builders::instruction_builder& builder, 
    byte base_value, operand<byte>& op, cpu_operation<byte, byte>& operation, byte cycles){
    for (int i=0; i<8; ++i){
        builder
            .operands(_cpu.operands().constant(i), op)
            .opcode(0xCB, base_value + i * 8)
            .cycles(cycles)
            .operation(operation)
            .add();
    }
}

void bitmask::add_bitmask_instruction(const std::string& name, const opcodes_struct& opcodes,
    cpu_operation<byte, byte> operation){
    builders::instruction_builder builder(_cpu, name);
    build_register_opcodes(builder, opcodes.A, _cpu.A, operation);
    build_register_opcodes(builder, opcodes.B, _cpu.B, operation);
    build_register_opcodes(builder, opcodes.C, _cpu.C, operation);
    build_register_opcodes(builder, opcodes.D, _cpu.D, operation);
    build_register_opcodes(builder, opcodes.E, _cpu.E, operation);
    build_register_opcodes(builder, opcodes.H, _cpu.H, operation);
    build_register_opcodes(builder, opcodes.L, _cpu.L, operation);
    build_register_opcodes(builder, opcodes.HL_mem, _cpu.operands().reg_mem(_cpu.HL), operation, 16);
    _set.add_instruction(builder.build());
}

void bitmask::initialize(){
    add_bitmask_instruction("bit", opcodes_struct {
        BIT_A,
        BIT_B,
        BIT_C,
        BIT_D,
        BIT_E,
        BIT_H,
        BIT_L,
        BIT_HL_mem
    }, bit_operation);

    add_bitmask_instruction("res", opcodes_struct {
        RES_A,
        RES_B,
        RES_C,
        RES_D,
        RES_E,
        RES_H,
        RES_L,
        RES_HL_mem
        }, res_operation
    );

    add_bitmask_instruction("set", opcodes_struct {
        SET_A,
        SET_B,
        SET_C,
        SET_D,
        SET_E,
        SET_H,
        SET_L,
        SET_HL_mem
        }, set_operation
    );
}
