#pragma once
#include <gamekid/cpu/instruction_set.h>
#include <gamekid/cpu/cpu.h>
#include <gamekid/system.h>

namespace gamekid::cpu::impl {
    class mem {
    public:
        static void initialize(system& system, instruction_set& set);
        static void push(cpu& cpu, word value);
        static word pop(cpu& cpu);

        static void ldd_operation(cpu& cpu, operand<byte>& dst, operand<byte>& src);
        static void push_operation(cpu& cpu, operand<word>& dst);
        static void pop_operation(cpu& cpu, operand<word>& dst);
    };
}