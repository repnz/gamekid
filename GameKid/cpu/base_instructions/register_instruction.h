#pragma once
#include "GameKid/cpu/instruction.h"
#include "GameKid/cpu/base_opcodes/register_opcode.h"

class register_instruction : public instruction
{
private:
    std::map<std::string, register_opcode> _register_opcodes;
protected:
    register_instruction(cpu& cpu, std::string name, bool cb_prefix, byte a, byte b, byte c,
        byte d, byte e, byte h, byte l);
public:


    std::vector<byte> parse(const std::vector<std::string>& operands) override;

    virtual void run(byte* val) = 0;

private:
    std::function<void(byte*)> _operation;

    void add_register_opcode(
        const byte value,
        const std::string& register_name,
        byte* register_address,
        bool cb_prefix,
        byte cycles
    );
};

