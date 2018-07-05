#pragma once
#include "opcode.h"
#include <functional>
#include <gamekid/cpu/cpu_operation.h>
#include <gamekid/utils/functional.h>
#include <gamekid/utils/str.h>

namespace gamekid::cpu {
    template <typename... operand_types>
    using operand_tuple = std::tuple<operand<operand_types>&...>;

    template <typename... operand_types>
    class operands_opcode : public opcode
    {
    private:
        cpu_operation<operand_types...> _operation;
        operand_tuple<operand_types...> _operands;
    public:
        operands_opcode(cpu& cpu, const std::string& name, const std::vector<byte>& value, byte cycles,
            operand_tuple<operand_types...>& operands,
            cpu_operation<operand_types...> operation);

        void run() override;

        std::vector<byte> encode(const std::vector<std::string>& operands) const override;

        std::string to_str(const byte* next) const override;

        int full_size() const override;
    };

    template <typename ... operand_types>
    operands_opcode<operand_types...>::operands_opcode(
        cpu& cpu, const std::string& name, const std::vector<byte>& value,
        byte cycles, operand_tuple<operand_types...>& operands,
        cpu_operation<operand_types...> operation) :
        opcode(cpu, name, value, cycles), _operation(operation), _operands(operands){}

    template <typename ... operand_types>
    void operands_opcode<operand_types...>::run() {
        auto args = std::tuple_cat(std::tuple<cpu&>(_cpu), _operands);
        gamekid::utils::functional::forward_tuple(_operation, args);
    }

    template <typename ... operand_types>
    std::vector<byte> operands_opcode<operand_types...>
        ::encode(const std::vector<std::string>& operands) const {
        std::vector<byte> v;

        for (byte opcode_byte : value){
            v.push_back(opcode_byte);
        }

        int index = 0;

        gamekid::utils::functional::for_each(_operands, [&](auto& operand) {
            for (byte b : operand.encode(operands[index])) {
                v.push_back(b);
                ++index;
            }
        });

        return v;
    }

    template <typename ... operand_types>
    std::string operands_opcode<operand_types...>::to_str(const byte* next) const {
        std::vector<std::string> operands_str;

        gamekid::utils::functional::for_each(_operands, [&](auto& op) {
            operands_str.push_back(op.to_str(next));
        });

        return name + " " + gamekid::utils::str::join(operands_str);
    }

    template <typename ... operand_types>
    int operands_opcode<operand_types...>::full_size() const {
        int size = value.size();

        gamekid::utils::functional::for_each(_operands, [&](auto& op) {
            size += op.immidiate_size();
        });

        return size;
    }
}