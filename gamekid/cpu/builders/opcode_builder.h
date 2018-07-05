#pragma once
#include <string>
#include "gamekid/utils/types.h"
#include "gamekid/cpu/operand.h"
#include <functional>
#include <memory>
#include "gamekid/cpu/opcode.h"
#include "gamekid/cpu/operands_opcode.h"
#include "gamekid/cpu/cpu_operation.h"

namespace gamekid::cpu::builders { 
    template <typename... operand_types>
    class opcode_builder {
    private:
        cpu & _cpu;
        std::string _name;
        std::vector<byte> _opcodes;
        std::unique_ptr<operand_tuple<operand_types...>> _operands;
        byte _cycles;
        cpu_operation<operand_types...> _operation;
    public:
        explicit opcode_builder(cpu& cpu);

        opcode_builder& name(const std::string& name);

        opcode_builder& opcode(byte first);
        opcode_builder& opcode(byte first, byte second);

        opcode_builder& operands(operand<operand_types>&... operands);
        opcode_builder& cycles(byte cycles);
        opcode_builder& operation(cpu_operation<operand_types...> act);
        std::unique_ptr<gamekid::cpu::opcode> build();
    };

    template <typename ... operand_types>
    opcode_builder<operand_types...>::opcode_builder(cpu& cpu) :
        _cpu(cpu), _cycles(0) {}
    
    template <typename ... operand_types>
    opcode_builder<operand_types...>& opcode_builder<operand_types...>::name(const std::string& name){
        _name = name;
        return *this;
    }

    template <typename ... operand_types>
    opcode_builder<operand_types...>& opcode_builder<operand_types...>::opcode(byte first) {
        _opcodes = { first };
        return *this;
    }

    template <typename ... operand_types>
    opcode_builder<operand_types...>& opcode_builder<operand_types...>::opcode(byte first, byte second) {
        _opcodes = { first, second };
        return *this;
    }

    template <typename ... operand_types>
    opcode_builder<operand_types...>& 
        opcode_builder<operand_types...>::operands(operand<operand_types>&... operands) {
        _operands.reset(new operand_tuple<operand_types...>(operands...));
        return *this;
    }

    template <typename ... operand_types>
    opcode_builder<operand_types...>& opcode_builder<operand_types...>::cycles(byte cycles)
    {
        _cycles = cycles;
        return *this;
    }

    template <typename ... operand_types>
    opcode_builder<operand_types...>& opcode_builder<operand_types...>::operation(
        cpu_operation<operand_types...> operation) {
        _operation = operation;
        return *this;
    }

    template <typename ... operand_types>
    std::unique_ptr<opcode> opcode_builder<operand_types...>::build() {
        return std::make_unique<operands_opcode<operand_types...>>(
            _cpu,
            _name,
            _opcodes,
            _cycles,
            *_operands,
            _operation
            );
    }
}
