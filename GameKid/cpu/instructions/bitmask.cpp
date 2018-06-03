#include "bitmask.h"
#include <GameKid/cpu/builders/instruction_builder.h>
#include <GameKid/cpu/operands.h>
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction_set.h"

void bitmask::build_register_opcodes(instruction_builder& builder, 
    byte base_value, operand<byte>& op, byte cycles)
{
    for (int i=0; i<8; ++i)
    {
        builder
            .operands(_cpu.operands().constant(i), op)
            .opcode(CB_PREFIX, base_value + i * 8)
            .cycles(cycles)
            .add();
    }
}

void bitmask::add_bitmask_instruction(const std::string& name, const opcodes& opcodes,
    std::function<void(operand<byte>&, operand<byte>&)> operation)
{
    instruction_builder builder(_cpu);
    builder.name(name);
    build_register_opcodes(builder, opcodes.A, _cpu.A);
    build_register_opcodes(builder, opcodes.B, _cpu.B);
    build_register_opcodes(builder, opcodes.C, _cpu.C);
    build_register_opcodes(builder, opcodes.D, _cpu.D);
    build_register_opcodes(builder, opcodes.E, _cpu.E);
    build_register_opcodes(builder, opcodes.H, _cpu.H);
    build_register_opcodes(builder, opcodes.L, _cpu.L);
    build_register_opcodes(builder, opcodes.HL, _cpu.operands().reg_mem(_cpu.HL), 16);
    builder.operation(operation);
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
    },
    [this](operand<byte>& bit, operand<byte>& byte_to_check)
    {
        _cpu.bit(byte_to_check.load(), bit.load());
    }
    );

    add_bitmask_instruction("res", opcodes{
        RES_A,
        RES_B,
        RES_C,
        RES_D,
        RES_E,
        RES_H,
        RES_L,
        RES_HL
        },
        [this](operand<byte>& bit, operand<byte>& byte_to_change)
    {
        byte value = byte_to_change.load();
        _cpu.res(&value, bit.load());
        byte_to_change.store(value);
    }
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
        },
        [this](operand<byte>& bit, operand<byte>& byte_to_set)
    {
        byte value = byte_to_set.load();
        _cpu.set(&value, bit.load());
        byte_to_set.store(value);
    }
    );
}
