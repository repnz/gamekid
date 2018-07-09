#pragma once
#include <gamekid/cpu/cpu.h>
#include <gamekid/memory/memory.h>
#include <functional>
#include "rom/cartridge.h"
#include "memory/gameboy_memory_map.h"
#include "memory/error_memory_map.h"

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
        memory::memory_map& _map;
        gamekid::memory::memory _memory;
        gamekid::cpu::cpu _cpu;
        std::vector<scheduled_operation> _scheduled_operations;
    public:
        explicit system(memory::memory_map& map) : 
        _map(map), _memory(_map), _cpu(*this){
        }

        system() : system(memory::error_memory_map::instance()){
            
        }

        system(const system&) = delete;
        system& operator=(const system&) = delete;

        cpu::cpu& cpu() {
            return _cpu;
        }

        memory::memory& memory() {
            return _memory;
        }

        void schedule_operation(system_operation<> operation, int instruction_count);
    };
}
