#pragma once
#include <functional>
#include <gamekid/cpu/builders/instruction_builder.h>
#include <gamekid/cpu/instruction_set.h>
#include <gamekid/cpu/impl/opcodes_struct.h>

namespace gamekid::cpu::impl {
    class bitmask {
    private:
        cpu & _cpu;
        instruction_set& _set;

        void build_register_opcodes(
            builders::instruction_builder& builder,
            byte base_value,
            operand<byte>& op,
            cpu_operation<byte, byte>& operation,
            byte cycles = 8
        );

        void add_bitmask_instruction(
            const std::string& name,
            const opcodes_struct& opcodes,
            cpu_operation<byte, byte> operation
        );
    public:
        bitmask(cpu& cpu, instruction_set& set) : _cpu(cpu), _set(set) {}

        void initialize();
        static void bit_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_check);
        static void res_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change);
        static void set_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change);
    };
}