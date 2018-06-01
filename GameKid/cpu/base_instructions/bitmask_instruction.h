#pragma once
#include "GameKid/cpu/opcode.h"
#include "GameKid/cpu/instruction.h"
#include "GameKid/cpu/base_opcodes/register_opcode.h"
#include <functional>
#include <map>

class bitmask_opcode : public opcode
{
private:
    byte _bit;
    std::function<void(byte*, byte)> _operation;
    reg8& _register;
public:
    bitmask_opcode(
        cpu& cpu,
        const std::string& name,
        byte base_value,
        reg8& reg,
        std::function<void(byte*, byte)> operation,
        byte bit
    );


    void run() override;
    std::string to_str(byte* next) override;
};

class bitmask_instruction : public instruction
{
public:
    bitmask_instruction(cpu& cpu, const std::string& name, const register_opcode_values& values);

    std::vector<byte> parse(const std::vector<std::string>& operands) override;

    virtual void run(byte* address, byte bit) = 0;
private:
    void add_register_opcodes(reg8& reg, byte base_value);

    std::function<void(byte*, byte)> _operation;
    bool _cb_prefix;
    std::map<std::string, std::vector<bitmask_opcode>> _bit_opcodes;

};

