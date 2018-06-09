#include "GameKid/cpu/instruction_set.h"
#include "alu_8.h"
#include "GameKid/cpu/builders/instruction_builder.h"
#include "GameKid/opcodes.h"
#include "GameKid/cpu/operands.h"

void add_operation(cpu& cpu, operand<byte>& op)
{
    cpu.add(cpu.A.address(), op.load());
}

void adc_operation(cpu& cpu, operand<byte>& op)
{
    op.store(op.load() + 1);
}

void sub_operation(cpu& cpu, operand<byte>& op)
{
    cpu.sub(cpu.A.address(), op.load());
}

void sbc_operation(cpu& cpu, operand<byte>& op)
{
    cpu.sbc(cpu.A.address(), op.load());
}

void and_operation(cpu& cpu, operand<byte>& op)
{
    cpu.and_n(cpu.A.address(), op.load());
}

void or_operation(cpu& cpu, operand<byte>& op)
{
    cpu.cp(cpu.A.load(), op.load());
}

void xor_operation(cpu& cpu, operand<byte>& op)
{
    cpu.xor_n(cpu.A.address(), op.load());
}

void cp_operation(cpu& cpu, operand<byte>& op)
{
    cpu.cp(cpu.A.load(), op.load());
}


void inc_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.inc(&val);
    op.store(val);
}

void dec_operation(cpu& cpu, operand<byte>& op)
{
    byte val = op.load();
    cpu.dec(&val);
    op.store(val);
}

void inc_word_operation(cpu& cpu, operand<word>& op)
{
    op.store(op.load() + 1);
}

void dec_word_operation(cpu& cpu, operand<word>& op)
{
    op.store(op.load() - 1);
}

void alu_8::initialize()
{
    add_alu_instruction("add", opcodes {
                            ADD_A_A,
                            ADD_A_B,
                            ADD_A_C,
                            ADD_A_D,
                            ADD_A_E,
                            ADD_A_H,
                            ADD_A_L,
                            ADD_A_HL,
                            ADD_A_IMM,
                        }, add_operation
    );

    add_alu_instruction("adc", opcodes{
                            ADC_A_A,
                            ADC_A_B,
                            ADC_A_C,
                            ADC_A_D,
                            ADC_A_E,
                            ADC_A_H,
                            ADC_A_L,
                            ADC_A_HL,
                            ADC_A_IMM,
                        }, adc_operation);

    add_alu_instruction("sub", opcodes {
                            SUB_A_A,
                            SUB_A_B,
                            SUB_A_C,
                            SUB_A_D,
                            SUB_A_E,
                            SUB_A_H,
                            SUB_A_L,
                            SUB_A_HL,
                            SUB_A_IMM,
                        }, sub_operation);

    add_alu_instruction("sbc", opcodes {
                            SBC_A_A,
                            SBC_A_B,
                            SBC_A_C,
                            SBC_A_D,
                            SBC_A_E,
                            SBC_A_H,
                            SBC_A_L,
                            SBC_A_HL,
                            SBC_A_IMM,
                        }, sbc_operation);

    

    add_alu_instruction("and", opcodes{
                            AND_A_A,
                            AND_A_B,
                            AND_A_C,
                            AND_A_D,
                            AND_A_E,
                            AND_A_H,
                            AND_A_L,
                            AND_A_HL,
                            AND_A_IMM,
                        }, and_operation);

    add_alu_instruction("or", opcodes{
                            OR_A,
                            OR_B,
                            OR_C,
                            OR_D,
                            OR_E,
                            OR_H,
                            OR_L,
                            OR_HL,
                            OR_IMM,
                        }, or_operation);

    add_alu_instruction("xor", opcodes{
                            XOR_A,
                            XOR_B,
                            XOR_C,
                            XOR_D,
                            XOR_E,
                            XOR_H,
                            XOR_L,
                            XOR_HL,
                            XOR_IMM,
                        }, xor_operation);

    add_alu_instruction("cp", opcodes{
                            CP_A,
                            CP_B,
                            CP_C,
                            CP_D,
                            CP_E,
                            CP_H,
                            CP_L,
                            CP_HL,
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

void alu_8::add_alu_instruction(const std::string& name, const opcodes& opcodes, cpu_operation<byte> operation)
{
    _set.add_instruction(instruction_builder(_cpu, name)
        .operands(_cpu.A).opcode(opcodes.A).cycles(4).operation(operation).add()
        .operands(_cpu.B).opcode(opcodes.B).cycles(4).operation(operation).add()
        .operands(_cpu.C).opcode(opcodes.C).cycles(4).operation(operation).add()
        .operands(_cpu.D).opcode(opcodes.D).cycles(4).operation(operation).add()
        .operands(_cpu.E).opcode(opcodes.E).cycles(4).operation(operation).add()
        .operands(_cpu.H).opcode(opcodes.H).cycles(4).operation(operation).add()
        .operands(_cpu.L).opcode(opcodes.L).cycles(4).operation(operation).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).opcode(opcodes.HL).operation(operation).cycles(8).add()
        .operands(_cpu.operands().immidiate_byte()).opcode(opcodes.IMM).operation(operation).cycles(8).add()
        .build()
        );
}
