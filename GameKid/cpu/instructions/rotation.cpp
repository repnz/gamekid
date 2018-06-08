#include <GameKid/cpu/instructions/rotation.h>
#include "GameKid/cpu/operands.h"
#include "GameKid/opcodes.h"

void rl_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.rl(&val);
    op.store(val);
}

void rr_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.rr(&val);
    op.store(val);
}

void rlc_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.rr(&val);
    op.store(val);
}

void rrc_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.rrc(&val);
    op.store(val);
}


void sla_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.sla(&val);
    op.store(val);
}

void srl_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.srl(&val);
    op.store(val);
}

void sra_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.sra(&val);
    op.store(val);
}


void rotation::initialize(instruction_set& set, cpu& c)
{
    set.add_instruction(instruction_builder(c, "rlca")
        .operands()
        .opcode(RLCA)
        .cycles(4)
        .operation([](cpu& cpu) { cpu.rlca(); })
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rra")
        .operands()
        .opcode(RRA)
        .cycles(4)
        .operation([](cpu& cpu) { cpu.rra(); })
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rla")
        .operands()
        .opcode(RLA)
        .cycles(4)
        .operation([](cpu& cpu) { cpu.rla(); })
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rrca")
        .operands()
        .opcode(RRCA)
        .cycles(4)
        .operation([](cpu& cpu) { cpu.rrca(); })
        .add().build()
    );

    set.add_instruction(instruction_builder(c, "rl")
        .operands(c.A).opcode(0xCB, CB_RL_A).operation(rl_operation).cycles(8).add()
        .operands(c.L).opcode(0xcb, CB_RL_B).operation(rl_operation).cycles(8).add()
        .operands(c.B).opcode(0xcb, CB_RL_C).operation(rl_operation).cycles(8).add()
        .operands(c.C).opcode(0xcb, CB_RL_D).operation(rl_operation).cycles(8).add()
        .operands(c.D).opcode(0xcb, CB_RL_E).operation(rl_operation).cycles(8).add()
        .operands(c.E).opcode(0xcb, CB_RL_H).operation(rl_operation).cycles(8).add()
        .operands(c.H).opcode(0xcb, CB_RL_L).operation(rl_operation).cycles(8).add()
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
            .operands(c.L).opcode(0xcb, CB_SRL_H).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(0xcb, CB_SRL_L).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(CB_SRL_HL).cycles(16).add()
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
