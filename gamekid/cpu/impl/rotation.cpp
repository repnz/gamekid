#include <gamekid/cpu/impl/rotation.h>
#include <gamekid/utils/bits.h>
#include <gamekid/cpu/opcodes.h>
#include <gamekid/cpu/builders/instruction_builder.h>
#include <gamekid/cpu/operands_container.h>

using namespace gamekid::cpu;
using namespace gamekid::cpu::impl;

void base_rl_operation(cpu& cpu, operand<byte>& op, bool move_carry){
    const byte value = op.load();
    byte new_value = (value << 1);

    if (move_carry) {
        new_value |= cpu.F.carry_bit();
    } else {
        new_value |= (value >> 7);
    }

    cpu.F.carry(gamekid::utils::bits::check_bit(value, 7));
    cpu.F.zero(new_value == 0);
    cpu.F.substract(false);
    cpu.F.half_carry(false);

    op.store(new_value);
}

void rotation::rl_operation(cpu& cpu, operand<byte>& op){
    base_rl_operation(cpu, op, false);
}

void rotation::rlc_operation(cpu& cpu, operand<byte>& op){
    base_rl_operation(cpu, op, true);
}

void rotation::rla_operation(cpu& cpu) {
    rl_operation(cpu, cpu.A);
}

void rotation::rlca_operation(cpu& cpu){
    rlc_operation(cpu, cpu.A);
}

void base_rr_operation(cpu& cpu, operand<byte>& op, bool move_carry){
    const byte value = op.load();
    byte new_value = value >> 1;

    if (move_carry){
        new_value |= (cpu.F.carry_bit() << 7);
    } else {
        new_value |= value << 7;
    }

    // update flags
    cpu.F.carry(gamekid::utils::bits::check_bit(value, 0));
    cpu.F.half_carry(false);
    cpu.F.substract(false);
    cpu.F.zero(new_value == 0);

    op.store(new_value);
}

void rotation::rr_operation(cpu& cpu, operand<byte>& op) {
    base_rr_operation(cpu, op, false);
}

void rotation::rrc_operation(cpu& cpu, operand<byte>& op){
    base_rr_operation(cpu, op, true);
}


void rotation::rra_operation(cpu& cpu) {
    rr_operation(cpu, cpu.A);
}


void rotation::rrca_operation(cpu& cpu) {
    rrc_operation(cpu, cpu.A);
}

void rotation::sla_operation(cpu& cpu, operand<byte>& op){
    const byte value = op.load();
    const byte new_value = value << 1;
    
    cpu.F.zero(new_value == 0);
    cpu.F.carry(gamekid::utils::bits::check_bit(value, 7));
    cpu.F.half_carry(false);
    cpu.F.substract(false);
    
    op.store(new_value);
}

void rotation::srl_operation(cpu& cpu, operand<byte>& op){
    const byte value = op.load();
    const byte new_value = value >> 1;

    cpu.F.zero(new_value == 0);
    cpu.F.carry(gamekid::utils::bits::check_bit(value, 0));
    cpu.F.half_carry(false);
    cpu.F.substract(false);

    op.store(new_value);
}

void rotation::sra_operation(cpu& cpu, operand<byte>& op){
    const byte value = op.load();
    const byte new_value = ((char)value) >> 1;
    
    cpu.F.zero(new_value == 0);
    cpu.F.carry(gamekid::utils::bits::check_bit(value, 0));
    cpu.F.half_carry(false);
    cpu.F.substract(false);

    op.store(new_value);
}


void rotation::initialize(instruction_set& set, cpu& c){
    set.add_instruction(builders::instruction_builder(c, "rlca")
        .operands()
        .opcode(RLCA)
        .cycles(4)
        .operation(rlca_operation)
        .add().build()
    );

    set.add_instruction(builders::instruction_builder(c, "rra")
        .operands()
        .opcode(RRA)
        .cycles(4)
        .operation(rra_operation)
        .add().build()
    );

    set.add_instruction(builders::instruction_builder(c, "rla")
        .operands()
        .opcode(RLA)
        .cycles(4)
        .operation(rla_operation)
        .add().build()
    );

    set.add_instruction(builders::instruction_builder(c, "rrca")
        .operands()
        .opcode(RRCA)
        .cycles(4)
        .operation(rrca_operation)
        .add().build()
    );

    set.add_instruction(builders::instruction_builder(c, "rl")
        .operands(c.A).opcode(RL_A).operation(rl_operation).cycles(8).add()
        .operands(c.B).opcode(RL_B).operation(rl_operation).cycles(8).add()
        .operands(c.C).opcode(RL_C).operation(rl_operation).cycles(8).add()
        .operands(c.D).opcode(RL_D).operation(rl_operation).cycles(8).add()
        .operands(c.E).opcode(RL_E).operation(rl_operation).cycles(8).add()
        .operands(c.H).opcode(RL_H).operation(rl_operation).cycles(8).add()
        .operands(c.L).opcode(RL_L).operation(rl_operation).cycles(8).add()
        .operands(c.operands().reg_mem(c.HL)).opcode(RL_HL_mem).operation(rl_operation).cycles(16).add()
        .build());

    set.add_instruction(builders::instruction_builder(c, "rr")
        .operands(c.A).opcode(RR_A).operation(rr_operation).cycles(8).add()
        .operands(c.B).opcode(RR_B).operation(rr_operation).cycles(8).add()
        .operands(c.C).opcode(RR_C).operation(rr_operation).cycles(8).add()
        .operands(c.D).opcode(RR_D).operation(rr_operation).cycles(8).add()
        .operands(c.E).opcode(RR_E).operation(rr_operation).cycles(8).add()
        .operands(c.L).opcode(RR_L).operation(rr_operation).cycles(8).add()
        .operands(c.H).opcode(RR_H).operation(rr_operation).cycles(8).add()
        .operands(c.operands().reg_mem(c.HL)).operation(rr_operation).opcode(RR_HL_mem).cycles(16).add()
        .build());
        
        set.add_instruction(builders::instruction_builder(c, "rlc")
            .operands(c.A).opcode(RLC_A).operation(rlc_operation).cycles(8).add()
            .operands(c.B).opcode(RLC_B).operation(rlc_operation).cycles(8).add()
            .operands(c.C).opcode(RLC_C).operation(rlc_operation).cycles(8).add()
            .operands(c.D).opcode(RLC_D).operation(rlc_operation).cycles(8).add()
            .operands(c.E).opcode(RLC_E).operation(rlc_operation).cycles(8).add()
            .operands(c.H).opcode(RLC_H).operation(rlc_operation).cycles(8).add()
            .operands(c.L).opcode(RLC_L).operation(rlc_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(rlc_operation).opcode(RLC_HL_mem).cycles(16).add()
            .build());

        set.add_instruction(builders::instruction_builder(c, "rrc")
            .operands(c.A).opcode(RRC_A).operation(rrc_operation).cycles(8).add()
            .operands(c.B).opcode(RRC_B).operation(rrc_operation).cycles(8).add()
            .operands(c.C).opcode(RRC_C).operation(rrc_operation).cycles(8).add()
            .operands(c.D).opcode(RRC_D).operation(rrc_operation).cycles(8).add()
            .operands(c.E).opcode(RRC_E).operation(rrc_operation).cycles(8).add()
            .operands(c.H).opcode(RRC_H).operation(rrc_operation).cycles(8).add()
            .operands(c.L).opcode(RRC_L).operation(rrc_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(rrc_operation).opcode(RRC_HL_mem).cycles(16).add()
            .build());


        set.add_instruction(builders::instruction_builder(c, "sla")
            .operands(c.A).opcode(SLA_A).operation(sla_operation).cycles(8).add()
            .operands(c.B).opcode(SLA_B).operation(sla_operation).cycles(8).add()
            .operands(c.C).opcode(SLA_C).operation(sla_operation).cycles(8).add()
            .operands(c.D).opcode(SLA_D).operation(sla_operation).cycles(8).add()
            .operands(c.E).opcode(SLA_E).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(SLA_H).operation(sla_operation).cycles(8).add()
            .operands(c.L).opcode(SLA_L).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(SLA_HL_mem).cycles(16).add()
            .build());

        set.add_instruction(builders::instruction_builder(c, "srl")
            .operands(c.A).opcode(SRL_A).operation(sla_operation).cycles(8).add()
            .operands(c.B).opcode(SRL_B).operation(sla_operation).cycles(8).add()
            .operands(c.C).opcode(SRL_C).operation(sla_operation).cycles(8).add()
            .operands(c.D).opcode(SRL_D).operation(sla_operation).cycles(8).add()
            .operands(c.E).opcode(SRL_E).operation(sla_operation).cycles(8).add()
            .operands(c.L).opcode(SRL_L).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(SRL_H).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(SRL_HL_mem).cycles(16).add()
            .build());

        set.add_instruction(builders::instruction_builder(c, "sra")
            .operands(c.A).opcode(SRA_A).operation(sla_operation).cycles(8).add()
            .operands(c.B).opcode(SRA_B).operation(sla_operation).cycles(8).add()
            .operands(c.C).opcode(SRA_C).operation(sla_operation).cycles(8).add()
            .operands(c.D).opcode(SRA_D).operation(sla_operation).cycles(8).add()
            .operands(c.E).opcode(SRA_E).operation(sla_operation).cycles(8).add()
            .operands(c.L).opcode(SRA_L).operation(sla_operation).cycles(8).add()
            .operands(c.H).opcode(SRA_H).operation(sla_operation).cycles(8).add()
            .operands(c.operands().reg_mem(c.HL)).operation(sla_operation).opcode(SRA_HL_mem).cycles(16).add()
            .build());
}
