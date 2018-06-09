#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu/instruction.h>
#include "opcode_builder.h"

template <typename... T>
class instruction_opcode_adder;

class instruction_builder
{
private:
    cpu& _cpu;
    void add_opcode(std::unique_ptr<opcode> opcode);
    template <typename... T>
    friend class instruction_opcode_adder;
public:
    std::unique_ptr<instruction> builded_instruction;
    instruction_builder(cpu& cpu, const std::string& name);

    template <typename... T>
    instruction_opcode_adder<T...> operands(operand<T>&... ops);
    std::unique_ptr<instruction> build();
};

#include "instruction_opcode_adder.h"

template <typename ... T>
instruction_opcode_adder<T...> instruction_builder::operands(operand<T>&... ops)
{
    return instruction_opcode_adder<T...>(_cpu, *this, ops...);
}

