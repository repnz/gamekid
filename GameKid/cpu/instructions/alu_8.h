#pragma once
#include <functional>
class instruction_set;

class alu_8
{
private:
    struct opcodes
    {
        byte A;
        byte B;
        byte C;
        byte D;
        byte E;
        byte H;
        byte L;
        byte HL;
        byte IMM;
    };

    void add_alu_instruction(
        const std::string& name,
        const opcodes& opcodes,
        std::function<void(operand<byte>&)> operation
    );

    instruction_set& _set;
    cpu & _cpu;
public:
    explicit alu_8(instruction_set& set, cpu& cpu) : _set(set), _cpu(cpu){}
    void initialize();
};
