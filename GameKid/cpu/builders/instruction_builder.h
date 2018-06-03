#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu/instruction.h>
#include "opcode_builder.h"
#include "instruction_opcode_adder.h"

class instruction_builder;

class instruction_builder
{
private:
    cpu & _cpu;
    std::string _name;
    std::vector<opcode_builder<byte>> _byte_opcode_builders;
    std::vector<opcode_builder<word>> _word_opcode_builders;

    template <typename T>
    std::vector<opcode_builder<T>>& opcode_builders(byte b)
    {
        return _byte_opcode_builders;
    }

    template <typename T>
    std::vector<opcode_builder<T>>& opcode_builders(word w)
    {
        return _word_opcode_builders;
    }
public:
    explicit instruction_builder(cpu& cpu) :
        _cpu(cpu),
        _name("")
    {
    }

    instruction_builder& name(const std::string& name)
    {
        _name = name;
        return *this;
    }

    template <typename T>
    instruction_opcode_adder<T> operands(operand<T>& first, operand<T>& second)
    {
        auto& vector = opcode_builders<T>(T(0));
        vector.push_back(opcode_builder<T>(_cpu));
        auto& opcode_builder = vector.back();
        opcode_builder.operands(first, second);
        return instruction_opcode_adder<T>(*this, opcode_builder);
    }

    template <typename T>
    instruction_opcode_adder<T> operands(operand<T>& first)
    {
        auto& vector = opcode_builders<T>(T(0));
        vector.push_back(opcode_builder<T>(_cpu));
        auto& opcode_builder = vector.back();
        opcode_builder.operands(first);
        return instruction_opcode_adder<T>(*this, opcode_builder);
    }
    
    template <typename T>
    instruction_builder& operation(std::function<void(operand<T>&)> act)
    {
        for (opcode_builder<T>& b : opcode_builders<T>(T()))
        {
            if (!b.has_operation())
            {
                b.operation(act);
            }
        }

        return *this;
    }

    template <typename T>
    instruction_builder& operation(std::function<void(operand<T>&, operand<T>&)> act)
    {
        for (auto& b : opcode_builders<T>(T()))
        {
            if (!b.has_operation())
            {
                b.operation(act);
            }
        }

        return *this;
    }

    std::unique_ptr<instruction> build();
};

