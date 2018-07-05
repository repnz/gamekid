#pragma once
#include <functional>
#include <gamekid/cpu/instruction_set.h>
#include "opcodes_struct.h"
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/cpu_operation.h>

namespace gamekid::cpu::impl { 
    class alu {
    private:

        void add_alu_instruction(
            const std::string& name,
            const opcodes_struct& opcodes,
            cpu_operation<byte> operation
        );

        instruction_set& _set;
        cpu & _cpu;
    public:
        explicit alu(instruction_set& set, cpu& cpu) : _set(set), _cpu(cpu) {}
        void initialize();

        // 8 bit operations
        static void add_operation(cpu& cpu, operand<byte>& op);
        static void adc_operation(cpu& cpu, operand<byte>& op);
        static void sub_operation(cpu& cpu, operand<byte>& op);
        static void sbc_operation(cpu& cpu, operand<byte>& op);
        static void and_operation(cpu& cpu, operand<byte>& op);
        static void or_operation(cpu& cpu, operand<byte>& op);
        static void xor_operation(cpu& cpu, operand<byte>& op);
        static void cp_operation(cpu& cpu, operand<byte>& op);
        static void inc_operation(cpu& cpu, operand<byte>& op);
        static void dec_operation(cpu& cpu, operand<byte>& op);

        // 16 bit operations
        static void inc_word_operation(cpu& cpu, operand<word>& op);
        static void dec_word_operation(cpu& cpu, operand<word>& op);
        static void add_to_hl_operation(cpu& cpu, operand<word>& hl, operand<word>& reg);
        static void add_to_sp_operation(cpu& cpu, operand<word>& sp, operand<byte>& reg);
    };
}