#pragma once
#include "GameKid/cpu/instruction.h"
#include "GameKid/cpu/base_opcodes/register_opcode.h"
#include <map>

class register_instruction : public instruction
{
private:
    std::map<std::string, register_opcode> _register_opcodes;
protected:
    register_instruction(cpu& cpu, std::string name, bool cb_prefix, const register_opcode_values& values);
public:


    std::vector<byte> parse(const std::vector<std::string>& operands) override;

    virtual void run(byte* val) = 0;

private:
    std::function<void(byte*)> _operation;

    void add_register_opcode(
        const byte value,
        reg8& reg,
        bool cb_prefix,
        byte cycles
    );
};

