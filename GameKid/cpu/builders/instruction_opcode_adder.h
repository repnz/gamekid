#pragma once
#include "opcode_builder.h"
#include <gamekid/cpu/cpu_operation.h>

namespace gamekid::cpu::builders {

    class instruction_builder;

    template <typename... operand_types>
    class instruction_opcode_adder {
    private:
        instruction_builder & _instruction_builder;
        opcode_builder<operand_types...> _opcode_builder;
    public:
        instruction_opcode_adder(gamekid::cpu::cpu& cpu, 
            instruction_builder& builder, gamekid::cpu::operand<operand_types>&...);

        template <typename... T>
        instruction_opcode_adder& opcode(T ... opcodes);

        instruction_opcode_adder& cycles(byte cycles);

        instruction_opcode_adder& operation(gamekid::cpu::cpu_operation<operand_types...> act);

        instruction_builder& add();
    };
}

#include "instruction_builder.h"

namespace gamekid::cpu::builders {
    
    template <typename ... operand_types>
    instruction_opcode_adder<operand_types...>::instruction_opcode_adder(cpu& cpu,
        instruction_builder& builder, operand<operand_types>&... operands) :
        _instruction_builder(builder),
        _opcode_builder(cpu) {
        _opcode_builder.name(builder.builded_instruction->name);
        _opcode_builder.operands(operands...);
    }

    template <typename ... operand_types>
    template <typename ... T>
    instruction_opcode_adder<operand_types...>& 
        instruction_opcode_adder<operand_types...>::opcode(T ... opcodes) {
        _opcode_builder.opcode(opcodes...);
        return *this;
    }

    template <typename ... operand_types>
    instruction_opcode_adder<operand_types...>& instruction_opcode_adder<operand_types...>::cycles(byte cycles) {
        _opcode_builder.cycles(cycles);
        return *this;
    }

    template <typename ... operand_types>
    instruction_opcode_adder<operand_types...>& instruction_opcode_adder<operand_types...>::operation(
        gamekid::cpu::cpu_operation<operand_types...> act){
        _opcode_builder.operation(act);
        return *this;
    }

    template <typename ... operand_types>
    instruction_builder& instruction_opcode_adder<operand_types...>::add(){
        _instruction_builder.add_opcode(_opcode_builder.build());
        return _instruction_builder;
    }

}
