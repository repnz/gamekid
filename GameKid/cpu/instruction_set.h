#pragma once
#include <gamekid/cpu/instruction.h>
#include <memory>
#include <vector>

namespace gamekid::cpu {
    class instruction_set {
    private:
        std::vector<std::unique_ptr<instruction>> _instructions;
        std::vector<instruction*> _ptr_instructions;
    public:
        cpu & _cpu;
        const std::vector<instruction*>& instructions();
        explicit instruction_set(cpu& cpu);
        void add_instruction(std::unique_ptr<instruction> instruction);

        std::vector<instruction*>::iterator begin() { return _ptr_instructions.begin(); }
        std::vector<instruction*>::iterator end() { return _ptr_instructions.end(); }

        std::vector<instruction*>::const_iterator begin() const { return _ptr_instructions.cbegin(); }
        std::vector<instruction*>::const_iterator end() const { return _ptr_instructions.cend(); }
    };
}