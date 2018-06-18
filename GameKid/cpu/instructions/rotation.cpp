#include <GameKid/cpu/instructions/rotation.h>
#include "GameKid/cpu/operands.h"
#include "GameKid/opcodes.h"

void base_rl_operation(cpu& cpu, operand<byte>& op, bool move_carry)
{
    const byte value = op.load();
    byte new_value = (value << 1);

    if (move_carry) 
    {
        new_value |= cpu.F.carry_bit();
    }
    else 
    {
        new_value |= (value >> 7);
    }

    cpu.F.carry(bits::check_bit(value, 7));
    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.half_carry(false);

    op.store(new_value);
}

void rotation::rl_operation(cpu& cpu, operand<byte>& op)
{
    base_rl_operation(cpu, op, false);
}

void rotation::rlc_operation(cpu& cpu, operand<byte>& op)
{
    base_rl_operation(cpu, op, true);
}

void rotation::rla_operation(cpu& cpu) 
{
    rl_operation(cpu, cpu.A);
}

void rotation::rlca_operation(cpu& cpu)
{
    rlc_operation(cpu, cpu.A);
}

void base_rr_operation(cpu& cpu, operand<byte>& op, bool move_carry)
{
    const byte value = op.load();
    byte new_value = value >> 1;

    if (move_carry)
    {
        new_value |= (cpu.F.carry_bit() << 7);
    }
    else 
    {
        new_value |= value << 7;
    }

    // update flags
    cpu.F.carry(bits::check_bit(value, 0));
    cpu.F.half_carry(false);
    cpu.F.substract(false);
    cpu.F.zero(new_value == 0);

    op.store(new_value);
}

void rotation::rr_operation(cpu& cpu, operand<byte>& op)
{
    base_rr_operation(cpu, op, false);
}

void rotation::rrc_operation(cpu& cpu, operand<byte>& op)
{
    base_rr_operation(cpu, op, true);
}


void rotation::rra_operation(cpu& cpu) 
{
    rr_operation(cpu, cpu.A);
}


void rotation::rrca_operation(cpu& cpu) 
{
    rrc_operation(cpu, cpu.A);
}

void rotation::sla_operation(cpu& cpu, operand<byte>& op)
{
    const byte value = op.load();
    const byte new_value = value << 1;
    
    cpu.F.zero(new_value == 0);
    cpu.F.carry(bits::check_bit(value, 7));
    cpu.F.half_carry(false);
    cpu.F.substract(false);
    
    op.store(new_value);
}

void rotation::srl_operation(cpu& cpu, operand<byte>& op)
{
    const byte value = op.load();
    const byte new_value = value >> 1;

    cpu.F.zero(new_value == 0);
    cpu.F.carry(bits::check_bit(value, 0));
    cpu.F.half_carry(false);
    cpu.F.substract(false);

    op.store(new_value);
}

void rotation::sra_operation(cpu& cpu, operand<byte>& op)
{
    const byte value = op.load();
    const byte new_value = ((char)value) >> 1;
    
    cpu.F.zero(new_value == 0);
    cpu.F.carry(bits::check_bit(value, 0));
    cpu.F.half_carry(false);
    cpu.F.substract(false);

    op.store(new_value);
}


void rotation::initialize(instruction_set& set, cpu& c)
{
    set.add_instruction(instruction_builder(c, "rlca")
        .operands()
        .opcode(RLCA)
        .cycles(4)
        .operation(rlca_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rra")
        .operands()
        .opcode(RRA)
        .cycles(4)
        .operation(rra_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rla")
        .operands()
        .opcode(RLA)
        .cycles(4)
        .operation(rla_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rrca")
        .operands()
        .opcode(RRCA)
        .cycles(4)
        .operation(rrca_operation)
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rl")
        .operands(c.A).opcode(0xCB, CB_RL_A).operation(rl_operation).cycles(8).add()
        .operands(c.B).opcode(0xcb, CB_RL_B).operation(rl_operation).cycles(8).add()
        .operands(c.C).opcode(0xcb, CB_RL_C).operation(rl_operation).cycles(8).add()
        .operands(c.D).opcode(0xcb, CB_RL_D).operation(rl_operation).cycles(8).add()
        .operands(c.E).opcode(0xcb, CB_RL_E).operation(rl_operation).cycles(8).add()
        .operands(c.H).opcode(0xcb, CB_RL_H).operation(rl_operation).cycles(8).add()
        .operands(c.L).opcode(0xcb, CB_RL_L).operation(rl_operation).cycles(8).add()
        .operands(c.operands().reg_mem(c.HL)).opcode(0xcb, CB_RL_HL).operation(rl_operation).cycles(16).add()
        .build());

    set.add_instruction(instruction_builder(c, "rr")
        .operands(c.A).opcode(0xCB, CB_RR_A).operation(rr_operation).cycles(8).add()
        .operands(c.B).opcode(0xcb, CB_RR_B).operation(rr_operation).cycles(8).add()
        .operands(c.C).opcode(0xcb, CB_RR_C).operation(rr_operation).cycles(8).add()
        .operands(c.D).opcode(0xcb, CB_RR_D).operation(rr_operation).cycles(8).add()
        .operands(c.E).opcode(0xcb, CB_RR_E).operation(rr_operation).cycles(8).add()
        .operands(c.L).opcode(0xcb, CB_RR_H).operation(rr_operation).cycles(8).add()
        .operands(c.H).opcode(0xcb, CB_RR_L).operation(rr_operation).cycles(8).add()
        .operands(c.operands().reg_mem(c.HL)).operation(rr_operation).opcode(0xcb, CB_RR_HL).cycles(16).add()
        .build());
        
        set.add_instruction(instruction_builder(c, "rlc")
            .operands(c.A).opcode(0xCB, CB_RLC_A).operation(rlc_operation).cycles(8).add()
            .operands(c.B).opcode(0xcb, CB_RLC_B).operation(rlc_operation).cycles(8).add()
            .operands(c.C).opcode(0xcb, CB_RLC_C).operation(rlc_operation).cycles(8).add()
            .operands(c.D).opcode(0xcb, CB_RLC_D).operation(rlc_operation).cycles(8).add()
            .operands(c.E).opcode(0xcb, CB_RLC_E).operation(rlc_operation).cycles(8).add()
            .operands(c.L).opcode(0xcb, CB_RLC_H).operation(rlc_operation).cycles(8).add()
            .operands(c.H).opcode(0xcb, CB_RLC_L).operation(rlc_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(rlc_operation).opcode(0xcb, CB_RLC_HL).cycles(16).add()
            .build());

        set.add_instruction(instruction_builder(c, "rrc")
            .operands(c.A).opcode(0xCB, CB_RRC_A).operation(rrc_operation).cycles(8).add()
            .operands(c.B).opcode(0xcb, CB_RRC_B).operation(rrc_operation).cycles(8).add()
            .operands(c.C).opcode(0xcb, CB_RRC_C).operation(rrc_operation).cycles(8).add()
            .operands(c.D).opcode(0xcb, CB_RRC_D).operation(rrc_operation).cycles(8).add()
            .operands(c.E).opcode(0xcb, CB_RRC_E).operation(rrc_operation).cycles(8).add()
            .operands(c.L).opcode(0xcb, CB_RRC_H).operation(rrc_operation).cycles(8).add()
            .operands(c.H).opcode(0xcb, CB_RRC_L).operation(rrc_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(rrc_operation).opcode(0xcb, CB_RRC_HL).cycles(16).add()
            .build());


        set.add_instruction(instruction_builder(c, "sla")
            .operands(c.A).opcode(0xCB, CB_SLA_A).operation(sla_operation).cycles(8).add()
            .operands(c.B).opcode(0xcb, CB_SLA_B).operation(sla_operation).cycles(8).add()
            .operands(c.C).opcode(0xcb, CB_SLA_C).operation(sla_operation).cycles(8).add()
            .operands(c.D).opcode(0xcb, CB_SLA_D).operation(sla_operation).cycles(8).add()
            .operands(c.E).opcode(0xcb, CB_SLA_E).operation(sla_operation).cycles(8).add()
            .operands(c.L).opcode(0xcb, CB_SLA_H).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(0xcb, CB_SLA_L).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(0xcb, CB_SLA_HL).cycles(16).add()
            .build());

        set.add_instruction(instruction_builder(c, "srl")
            .operands(c.A).opcode(0xCB, CB_SRL_A).operation(sla_operation).cycles(8).add()
            .operands(c.B).opcode(0xcb, CB_SRL_B).operation(sla_operation).cycles(8).add()
            .operands(c.C).opcode(0xcb, CB_SRL_C).operation(sla_operation).cycles(8).add()
            .operands(c.D).opcode(0xcb, CB_SRL_D).operation(sla_operation).cycles(8).add()
            .operands(c.E).opcode(0xcb, CB_SRL_E).operation(sla_operation).cycles(8).add()
            .operands(c.L).opcode(0xcb, CB_SRL_L).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(0xcb, CB_SRL_H).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(0xcb, CB_SRL_HL).cycles(16).add()
            .build());

        set.add_instruction(instruction_builder(c, "sra")
            .operands(c.A).opcode(0xCB, CB_SRA_A).operation(sla_operation).cycles(8).add()
            .operands(c.B).opcode(0xcb, CB_SRA_B).operation(sla_operation).cycles(8).add()
            .operands(c.C).opcode(0xcb, CB_SRA_C).operation(sla_operation).cycles(8).add()
            .operands(c.D).opcode(0xcb, CB_SRA_D).operation(sla_operation).cycles(8).add()
            .operands(c.E).opcode(0xcb, CB_SRA_E).operation(sla_operation).cycles(8).add()
            .operands(c.L).opcode(0xcb, CB_SRA_H).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(0xcb, CB_SRA_L).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(0xcb, CB_SRA_HL).cycles(16).add()
            .build());
}
