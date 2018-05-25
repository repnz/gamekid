#pragma once
#include <vector>
#include <GameKid/cpu/instruction.h>
#include <memory>


class instruction_set
{
private:
    cpu & _cpu;
    std::vector<std::unique_ptr<instruction>> _instructions;
    std::vector<instruction*> _ptr_instructions;
public:
    const std::vector<instruction*>& instructions();
    explicit instruction_set(cpu& cpu);

    template <typename T>
    void add()
    {
        std::unique_ptr<T> smart_ptr = std::make_unique<T>(_cpu);
        instruction* ptr = smart_ptr.get();
        _instructions.push_back(std::move(smart_ptr));
        _ptr_instructions.push_back(ptr);
    }

};
