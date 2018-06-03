#pragma once
#include "opcode_builder.h"

class instruction_builder;

template <typename T>
class instruction_opcode_adder
{
private:
    instruction_builder & _instruction_builder;
    opcode_builder<T> _opcode_builder;
public:
    explicit instruction_opcode_adder(instruction_builder& builder, opcode_builder<T>& opcode_builder) :
        _instruction_builder(builder),
        _opcode_builder(opcode_builder)
    {
    }

    instruction_opcode_adder& opcode(byte value)
    {
        _opcode_builder.opcode(value);
        return *this;
    }

    instruction_opcode_adder& opcode(byte first_opcode, byte second_opcode)
    {
        _opcode_builder.opcode(first_opcode, second_opcode);
        return *this;
    }
    instruction_opcode_adder& cycles(byte cycles)
    {
        _opcode_builder.cycles(cycles);
        return *this;
    }
    
    instruction_opcode_adder& operation(std::function<void(operand<T>&, operand<T>&)> act)
    {
        _opcode_builder.operation(act);
        return *this;
    }

    instruction_opcode_adder& operation(std::function<void(operand<T>&)> act)
    {
        _opcode_builder.operation(act);
        return *this;
    }



    instruction_builder& add()
    {
        return _instruction_builder;
    }
};

