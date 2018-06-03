#include <GameKid/cpu/instructions/rotation.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"
#include "GameKid/cpu/operands.h"
#include "GameKid/opcodes.h"

void rotation::initialize(instruction_set& set, cpu& cpu)
{
    set.add_instruction(std::make_unique<single_opcode_instruction>(
        cpu,
        "rlca",
        std::vector<byte> {RLCA},
        4,
        [&cpu]() { cpu.rlca(); }
    ));

    set.add_instruction(std::make_unique<single_opcode_instruction>(
        cpu,
        "rra",
        std::vector<byte> {RRA},
        4,
        [&cpu]() { cpu.rra(); }
    ));

    set.add_instruction(std::make_unique<single_opcode_instruction>(
        cpu,
        "rla",
        std::vector<byte> {RLA},
        4,
        [&cpu]() { cpu.rla(); }
    ));

    set.add_instruction(std::make_unique<single_opcode_instruction>(
        cpu,
        "rrca",
        std::vector<byte> {RRCA},
        4,
        [&cpu]() { cpu.rrca(); }
    ));

    auto rl = [&cpu](operand<byte>& op)
    {
        byte val=  op.load();
        cpu.rl(&val);
        op.store(val);
    };

    set.add_instruction(instruction_builder(cpu)
        .name("rl")
        .operands(cpu.A).opcode(0xCB, CB_RL_A).cycles(8).add()
        .operands(cpu.L).opcode(0xcb, CB_RL_B).cycles(8).add()
        .operands(cpu.B).opcode(0xcb, CB_RL_C).cycles(8).add()
        .operands(cpu.C).opcode(0xcb, CB_RL_D).cycles(8).add()
        .operands(cpu.D).opcode(0xcb, CB_RL_E).cycles(8).add()
        .operands(cpu.E).opcode(0xcb, CB_RL_H).cycles(8).add()
        .operands(cpu.H).opcode(0xcb, CB_RL_L).cycles(8).add()
        .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_RL_HL).cycles(16).add()
        .operation<byte>(rl)
        .build());

    auto rr = [&cpu](operand<byte>& op)
    {
        byte val = op.load();
        cpu.rr(&val);
        op.store(val);
    };

    set.add_instruction(instruction_builder(cpu)
        .name("rr")
        .operands(cpu.A).opcode(0xCB, CB_RR_A).cycles(8).add()
        .operands(cpu.B).opcode(0xcb, CB_RR_B).cycles(8).add()
        .operands(cpu.C).opcode(0xcb, CB_RR_C).cycles(8).add()
        .operands(cpu.D).opcode(0xcb, CB_RR_D).cycles(8).add()
        .operands(cpu.E).opcode(0xcb, CB_RR_E).cycles(8).add()
        .operands(cpu.L).opcode(0xcb, CB_RR_H).cycles(8).add()
        .operands(cpu.H).opcode(0xcb, CB_RR_L).cycles(8).add()
        .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_RR_HL).cycles(16).add()
        .operation<byte>(rr)
        .build());
        
        auto rlc = [&cpu](operand<byte>& op)
        {
            byte val = op.load();
            cpu.rlc(&val);
            op.store(val);
        };

        set.add_instruction(instruction_builder(cpu)
            .name("rlc")
            .operands(cpu.A).opcode(0xCB, CB_RLC_A).cycles(8).add()
            .operands(cpu.B).opcode(0xcb, CB_RLC_B).cycles(8).add()
            .operands(cpu.C).opcode(0xcb, CB_RLC_C).cycles(8).add()
            .operands(cpu.D).opcode(0xcb, CB_RLC_D).cycles(8).add()
            .operands(cpu.E).opcode(0xcb, CB_RLC_E).cycles(8).add()
            .operands(cpu.L).opcode(0xcb, CB_RLC_H).cycles(8).add()
            .operands(cpu.H).opcode(0xcb, CB_RLC_L).cycles(8).add()
            .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_RLC_HL).cycles(16).add()
            .operation<byte>(rlc)
            .build());

        auto rrc = [&cpu](operand<byte>& op)
        {
            byte val = op.load();
            cpu.rrc(&val);
            op.store(val);
        };

        set.add_instruction(instruction_builder(cpu)
            .name("rrc")
            .operands(cpu.A).opcode(0xCB, CB_RRC_A).cycles(8).add()
            .operands(cpu.B).opcode(0xcb, CB_RRC_B).cycles(8).add()
            .operands(cpu.C).opcode(0xcb, CB_RRC_C).cycles(8).add()
            .operands(cpu.D).opcode(0xcb, CB_RRC_D).cycles(8).add()
            .operands(cpu.E).opcode(0xcb, CB_RRC_E).cycles(8).add()
            .operands(cpu.L).opcode(0xcb, CB_RRC_H).cycles(8).add()
            .operands(cpu.H).opcode(0xcb, CB_RRC_L).cycles(8).add()
            .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_RRC_HL).cycles(16).add()
            .operation<byte>(rrc)
            .build());

        auto sla = [&cpu](operand<byte>& op)
        {
            byte val = op.load();
            cpu.sla(&val);
            op.store(val);
        };

        set.add_instruction(instruction_builder(cpu)
            .name("sla")
            .operands(cpu.A).opcode(0xCB, CB_SLA_A).cycles(8).add()
            .operands(cpu.B).opcode(0xcb, CB_SLA_B).cycles(8).add()
            .operands(cpu.C).opcode(0xcb, CB_SLA_C).cycles(8).add()
            .operands(cpu.D).opcode(0xcb, CB_SLA_D).cycles(8).add()
            .operands(cpu.E).opcode(0xcb, CB_SLA_E).cycles(8).add()
            .operands(cpu.L).opcode(0xcb, CB_SLA_H).cycles(8).add()
            .operands(cpu.H).opcode(0xcb, CB_SLA_L).cycles(8).add()
            .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_SLA_HL).cycles(16).add()
            .operation<byte>(sla)
            .build());

        auto srl = [&cpu](operand<byte>& op)
        {
            byte val = op.load();
            cpu.srl(&val);
            op.store(val);
        };

        set.add_instruction(instruction_builder(cpu)
            .name("srl")
            .operands(cpu.A).opcode(0xCB, CB_SRL_A).cycles(8).add()
            .operands(cpu.B).opcode(0xcb, CB_SRL_B).cycles(8).add()
            .operands(cpu.C).opcode(0xcb, CB_SRL_C).cycles(8).add()
            .operands(cpu.D).opcode(0xcb, CB_SRL_D).cycles(8).add()
            .operands(cpu.E).opcode(0xcb, CB_SRL_E).cycles(8).add()
            .operands(cpu.L).opcode(0xcb, CB_SRL_H).cycles(8).add()
            .operands(cpu.H).opcode(0xcb, CB_SRL_L).cycles(8).add()
            .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_SRL_HL).cycles(16).add()
            .operation<byte>(srl)
            .build());

        auto sra = [&cpu](operand<byte>& op)
        {
            byte val = op.load();
            cpu.sra(&val);
            op.store(val);
        };

        set.add_instruction(instruction_builder(cpu)
            .name("sra")
            .operands(cpu.A).opcode(0xCB, CB_SRA_A).cycles(8).add()
            .operands(cpu.B).opcode(0xcb, CB_SRA_B).cycles(8).add()
            .operands(cpu.C).opcode(0xcb, CB_SRA_C).cycles(8).add()
            .operands(cpu.D).opcode(0xcb, CB_SRA_D).cycles(8).add()
            .operands(cpu.E).opcode(0xcb, CB_SRA_E).cycles(8).add()
            .operands(cpu.L).opcode(0xcb, CB_SRA_H).cycles(8).add()
            .operands(cpu.H).opcode(0xcb, CB_SRA_L).cycles(8).add()
            .operands(cpu.operands().reg_mem(cpu.HL)).opcode(CB_SRA_HL).cycles(16).add()
            .operation<byte>(sra)
            .build());
}
