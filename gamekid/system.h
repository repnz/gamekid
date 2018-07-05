#pragma once
#include <gamekid/cpu/cpu.h>
#include <gamekid/memory/memory.h>
#include <functional>

namespace gamekid {
    namespace cpu {
        class cpu;

        template <typename T>
        class operand;
    }

    class system;

    template <typename... operand_types>
    using system_operation = std::function<void(system&, cpu::operand<operand_types>&...)>;

    struct scheduled_operation {
        system_operation<> operation;
        int instruction_count;

        scheduled_operation(system_operation<> operation, int instruction_count) :
            operation(operation), instruction_count(instruction_count) {}
    };


    class system {
    private:
        gamekid::cpu::cpu _cpu;
        gamekid::memory::memory _memory;
        std::vector<scheduled_operation> _scheduled_operations;
    public:
        system(const std::vector<byte>& rom) : _cpu(*this), _memory(rom) {}

        system(const system&) = delete;

        cpu::cpu& cpu() {
            return _cpu;
        }

        memory::memory& memory() {
            return _memory;
        }

        void schedule_operation(system_operation<> operation, int instruction_count);
    };
}