#include <GameKid/cpu/instructions/misc.h>
#include <GameKid/cpu/builders/instruction_builder.h>
#include <GameKid/cpu/operands.h>
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction_set.h"


void swap_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.swap(&val);
    op.store(val);
}

void cpl_operation(cpu& cpu)
{
    cpu.A.store(~cpu.A.load());
    cpu.F.half_carry(true);
    cpu.F.substract(true);
}

void nop_operation(cpu& cpu)
{
    // do nothing 
}

void scf_operation(cpu& cpu)
{
    cpu.scf();
}

void stop_operation(cpu& cpu)
{
    cpu.stop();
}

void daa_operation(cpu& cpu)
{
    const byte left_digit = (cpu.A.load() & 0xF0) >> 4;
    const byte right_digit = (cpu.A.load() & 0x0F);

    if (left_digit > 10 || right_digit > 10)
    {
        // Error, what to do?
    }

    cpu.A.store(left_digit * 10 + right_digit);
    cpu.F.zero(cpu.A.load() == 0);
    cpu.F.substract(false);
    // what should be done with the carry flag?
}


void misc::initialize()
{
    _set.add_instruction(instruction_builder(_cpu, "swap")
        .operands(_cpu.A).opcode(CB_PREFIX, SWAP_A).operation(swap_operation).cycles(8).add()
        .operands(_cpu.B).opcode(CB_PREFIX, SWAP_B).operation(swap_operation).cycles(8).add()
        .operands(_cpu.C).opcode(CB_PREFIX, SWAP_C).operation(swap_operation).cycles(8).add()
        .operands(_cpu.D).opcode(CB_PREFIX, SWAP_D).operation(swap_operation).cycles(8).add()
        .operands(_cpu.E).opcode(CB_PREFIX, SWAP_E).operation(swap_operation).cycles(8).add()
        .operands(_cpu.H).opcode(CB_PREFIX, SWAP_H).operation(swap_operation).cycles(8).add()
        .operands(_cpu.L).opcode(CB_PREFIX, SWAP_L).operation(swap_operation).cycles(8).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).operation(swap_operation).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .build());

    _set.add_instruction(instruction_builder(_cpu, "cpl")
        .operands()
        .opcode(0x2F)
        .cycles(4)
        .operation(cpl_operation)
        .add().build()
    );

    _set.add_instruction(instruction_builder(_cpu, "nop")
        .operands()
        .opcode(NOP)
        .cycles(4)
        .operation(nop_operation) // do nothing
        .add().build()
    );

    _set.add_instruction(instruction_builder(_cpu, "scf")
        .operands()
        .opcode(SCF)
        .cycles(4)
        .operation(scf_operation) 
        .add().build()
    );

    _set.add_instruction(instruction_builder(_cpu, "stop")
        .operands()
        .opcode(0x10, 0)
        .cycles(4)
        .operation(stop_operation) 
        .add().build()
    );


    _set.add_instruction(instruction_builder(_cpu, "daa")
        .operands()
        .opcode(0x27)
        .cycles(4)
        .operation(daa_operation) 
        .add().build()
    );
}
