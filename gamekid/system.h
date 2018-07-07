#pragma once
#include <gamekid/cpu/cpu.h>
#include <gamekid/memory/memory.h>
#include <functional>
#include "rom/cartridge.h"

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
        rom::cartridge _cart;
        gamekid::cpu::cpu _cpu;
        gamekid::memory::memory _memory;
        std::vector<scheduled_operation> _scheduled_operations;
    public:
        explicit system(rom::cartridge&& cart) : _cart(cart), _cpu(*this), _memory(_cart){}
        explicit system(std::vector<byte>&& cart) : _cart(std::move(cart)), _cpu(*this), _memory(_cart){}


        system(const system&) = delete;
        system& operator=(const system&) = delete;

        cpu::cpu& cpu() {
            return _cpu;
        }

        memory::memory& memory() {
            return _memory;
        }

        rom::cartridge& cartridge() {
            return _cart;
        }

        void schedule_operation(system_operation<> operation, int instruction_count);
    };
}
