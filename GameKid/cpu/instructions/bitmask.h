#pragma once
#include <functional>
#include <GameKid/cpu/builders/instruction_builder.h>
class instruction_set;

class bitmask
{
private:
    cpu & _cpu;
    instruction_set& _set;
    
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
    };

    void build_register_opcodes(
        instruction_builder& builder,
        byte base_value,
        operand<byte>& op,
        cpu_operation<byte, byte>& operation,
        byte cycles = 8
    );

    void add_bitmask_instruction(
        const std::string& name,
        const opcodes& opcodes,
        cpu_operation<byte, byte> operation
    );
public:
    bitmask(cpu& cpu, instruction_set& set) : _cpu(cpu), _set(set){}

    void initialize();
    static void bit_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_check);
    static void res_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change);
    static void set_operation(cpu& cpu, operand<byte>& bit, operand<byte>& byte_to_change);
};


