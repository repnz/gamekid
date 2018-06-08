#include "bitmask.h"
#include <GameKid/cpu/builders/instruction_builder.h>
#include <GameKid/cpu/operands.h>
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction_set.h"

void bit_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_check)
{
    cpu.bit(byte_to_check.load(), bit.load());
}

void res_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change)
{
    byte value = byte_to_change.load();
    cpu.res(&value, bit.load());
    byte_to_change.store(value);
}

void set_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change)
{
    byte value = byte_to_change.load();
    cpu.set(&value, bit.load());
    byte_to_change.store(value);
}


void bitmask::build_register_opcodes(instruction_builder& builder, 
    byte base_value, operand<byte>& op, cpu_operation<byte, byte>& operation, byte cycles)
{
    for (int i=0; i<8; ++i)
    {
        builder
            .operands(_cpu.operands().constant(i), op)
            .opcode(CB_PREFIX, base_value + i * 8)
            .cycles(cycles)
            .operation(operation)
            .add();
    }
}

void bitmask::add_bitmask_instruction(const std::string& name, const opcodes& opcodes,
    cpu_operation<byte, byte> operation)
{
    instruction_builder builder(_cpu, name);
    build_register_opcodes(builder, opcodes.A, _cpu.A, operation);
    build_register_opcodes(builder, opcodes.B, _cpu.B, operation);
    build_register_opcodes(builder, opcodes.C, _cpu.C, operation);
    build_register_opcodes(builder, opcodes.D, _cpu.D, operation);
    build_register_opcodes(builder, opcodes.E, _cpu.E, operation);
    build_register_opcodes(builder, opcodes.H, _cpu.H, operation);
    build_register_opcodes(builder, opcodes.L, _cpu.L, operation);
    build_register_opcodes(builder, opcodes.HL, _cpu.operands().reg_mem(_cpu.HL), operation, 16);
    _set.add_instruction(builder.build());
}

void bitmask::initialize()
{
    add_bitmask_instruction("bit", opcodes {
        BIT_A,
        BIT_B,
        BIT_C,
        BIT_D,
        BIT_E,
        BIT_H,
        BIT_L,
        BIT_HL
    }, bit_operation);

    add_bitmask_instruction("res", opcodes{
        RES_A,
        RES_B,
        RES_C,
        RES_D,
        RES_E,
        RES_H,
        RES_L,
        RES_HL
        }, res_operation
    );

    add_bitmask_instruction("set", opcodes{
        SET_A,
        SET_B,
        SET_C,
        SET_D,
        SET_E,
        SET_H,
        SET_L,
        SET_HL
        }, set_operation
    );
}
