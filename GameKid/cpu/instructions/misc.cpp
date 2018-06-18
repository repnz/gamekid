#include <GameKid/cpu/instructions/misc.h>
#include <GameKid/cpu/builders/instruction_builder.h>
#include <GameKid/cpu/operands.h>
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction_set.h"


void misc::swap_operation(cpu& cpu, operand<byte>& op)
{
    const byte original_value = op.load();
    const byte swapped_value = original_value >> 4 | original_value << 4;
    op.store(swapped_value);

    cpu.F.zero(swapped_value == 0);
    cpu.F.substract(false);
    cpu.F.half_carry(false);
    cpu.F.carry(false);
}

void misc::cpl_operation(cpu& cpu)
{
    cpu.A.store(~cpu.A.load());
    cpu.F.half_carry(true);
    cpu.F.substract(true);
}

void misc::nop_operation(cpu& cpu)
{
    // do nothing 
}

void misc::scf_operation(cpu& cpu)
{
    cpu.F.half_carry(false);
    cpu.F.substract(false);
    cpu.F.carry(true);
}

void misc::stop_operation(cpu& cpu)
{
    cpu.stop();
}

void misc::daa_operation(cpu& cpu)
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


void misc::ccf_operation(cpu& cpu)
{
    cpu.F.substract(false);
    cpu.F.half_carry(false);
    cpu.F.carry(!cpu.F.carry());
}

void misc::halt_operation(cpu& cpu)
{ 
    cpu.halt(); 
}

void misc::ei_operation(cpu& cpu)
{
    cpu.schedule_operation([](class cpu& cpu)
    {
        cpu.enable_interrupts();
    }, 1);
}

void misc::di_operation(cpu& cpu)
{
    cpu.schedule_operation([](class cpu& cpu)
    {
        cpu.disable_interrupts();
    }, 1);
}

void misc::initialize(cpu& cpu, instruction_set& set)
{
    set.add_instruction(instruction_builder(cpu, "swap")
        .operands(cpu.A).opcode(CB_PREFIX, SWAP_A).operation(swap_operation).cycles(8).add()
        .operands(cpu.B).opcode(CB_PREFIX, SWAP_B).operation(swap_operation).cycles(8).add()
        .operands(cpu.C).opcode(CB_PREFIX, SWAP_C).operation(swap_operation).cycles(8).add()
        .operands(cpu.D).opcode(CB_PREFIX, SWAP_D).operation(swap_operation).cycles(8).add()
        .operands(cpu.E).opcode(CB_PREFIX, SWAP_E).operation(swap_operation).cycles(8).add()
        .operands(cpu.H).opcode(CB_PREFIX, SWAP_H).operation(swap_operation).cycles(8).add()
        .operands(cpu.L).opcode(CB_PREFIX, SWAP_L).operation(swap_operation).cycles(8).add()
        .operands(cpu.operands().reg_mem(cpu.HL)).operation(swap_operation).opcode(CB_PREFIX, SWAP_HL).cycles(8).add()
        .build());

    set.add_instruction(instruction_builder(cpu, "cpl")
        .operands()
        .opcode(0x2F)
        .cycles(4)
        .operation(cpl_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(cpu, "nop")
        .operands()
        .opcode(NOP)
        .cycles(4)
        .operation(nop_operation) // do nothing
        .add().build()
    );

    set.add_instruction(instruction_builder(cpu, "scf")
        .operands()
        .opcode(SCF)
        .cycles(4)
        .operation(scf_operation) 
        .add().build()
    );

    set.add_instruction(instruction_builder(cpu, "stop")
        .operands()
        .opcode(0x10, 0)
        .cycles(4)
        .operation(stop_operation) 
        .add().build()
    );


    set.add_instruction(instruction_builder(cpu, "daa")
        .operands()
        .opcode(0x27)
        .cycles(4)
        .operation(daa_operation) 
        .add().build()
    );

    set.add_instruction(instruction_builder(cpu, "ccf")
        .operands()
        .opcode(CCF)
        .cycles(4)
        .operation(ccf_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(cpu, "halt")
        .operands()
        .opcode(HALT)
        .cycles(4)
        .operation(halt_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(cpu, "ei")
        .operands()
        .opcode(0xFB)
        .cycles(4)
        .operation(ei_operation)
        .add().build());

    set.add_instruction(instruction_builder(cpu, "di")
        .operands()
        .opcode(0xF3)
        .cycles(4)
        .operation(di_operation)
        .add().build());
}
