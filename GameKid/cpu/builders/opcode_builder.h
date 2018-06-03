#pragma once
#include <string>
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/operand.h"
#include <functional>
#include <memory>
#include "GameKid/cpu/opcode.h"
#include "GameKid/cpu/two_operand_opcode.h"
#include "GameKid/cpu/single_operand_opcode.h"

template <typename operand_type>
class opcode_builder
{
private:
    cpu & _cpu;
    std::string _name;
    byte _first_opcode;
    byte _second_opcode;
    bool _has_two_bytes;
    bool _has_two_operands;
    operand<operand_type>* _first_operand;
    operand<operand_type>* _second_operand;
    byte _cycles;
    std::function<void(operand<operand_type>&)> _act1;
    std::function<void(operand<operand_type>&, operand<operand_type>&)> _act2;
public:
    explicit opcode_builder(cpu& cpu)
        : _cpu(cpu),
        _name(""),
        _first_opcode(0),
        _second_opcode(0),
        _has_two_bytes(false),
        _has_two_operands(false),
        _first_operand(nullptr),
        _second_operand(nullptr),
        _cycles(0),
        _act1(nullptr),
        _act2(nullptr)
    {
    }

    opcode_builder & name(const std::string& name)
    {
        _name = name;
        return *this;
    }

    opcode_builder& opcode(byte first)
    {
        _first_opcode = first;
        _has_two_bytes = false;
        return *this;

    }
    opcode_builder& opcode(byte first, byte second)
    {
        _first_opcode = first;
        _second_opcode = second;
        _has_two_bytes = true;
        return *this;
    }

    opcode_builder& operands(operand<operand_type>& operand)
    {
        _first_operand = &operand;
        _has_two_operands = false;
        return *this;
    }

    opcode_builder& operands(operand<operand_type>& first, operand<operand_type>& second)
    {
        _first_operand = &first;
        _second_operand = &second;
        _has_two_operands = true;
        return *this;
    }

    opcode_builder& cycles(byte cycles)
    {
        _cycles = cycles;
        return *this;
    }

    opcode_builder& operation(std::function<void(operand<operand_type>&)> act)
    {
        _act1 = act;
        return *this;
    }

    opcode_builder& operation(std::function<void(operand<operand_type>&, operand<operand_type>&)> act)
    {
        _act2 = act;
        return *this;
    }


    std::unique_ptr<::opcode> build()
    {
        std::vector<byte> v = opcode_vector();

        if (_has_two_operands)
        {
            return std::unique_ptr<::opcode>(
                new two_operand_opcode<operand_type>(_cpu,
                    _name, v, _cycles, *_first_operand, *_second_operand, _act2)
                );
        }

        return std::unique_ptr<::opcode>(new single_operand_opcode<operand_type >(_cpu,
            _name, v, _cycles, *_first_operand, _act1));
    }

private:
    std::vector<byte> opcode_vector()
    {
        if (_has_two_bytes)
        {
            return { _first_opcode, _second_opcode };
        }
        return { _first_opcode };
    }
};
