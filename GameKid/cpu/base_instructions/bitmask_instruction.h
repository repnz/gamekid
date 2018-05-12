#pragma once
#include "GameKid/cpu/opcode.h"
#include "GameKid/cpu/instruction.h"

class bitmask_opcode : public opcode
{
private:
    byte _bit;
    std::function<void(byte*, byte)> _operation;
    byte* register_address;
    std::string register_name;
public:
    bitmask_opcode(
        cpu& cpu,
        const std::string& name,
        byte base_value,
        const std::string& register_name,
        byte* register_address,
        std::function<void(byte*, byte)> operation,
        byte bit
    );


    void run() override;
    std::string to_str(byte* next) override;
};

class bitmask_instruction : public instruction
{
public:
    bitmask_instruction(cpu& cpu, const std::string& name,
        byte a,
        byte b,
        byte c,
        byte d,
        byte e,
        byte h,
        byte l);

    std::vector<byte> parse(const std::vector<std::string>& operands) override;

    virtual void run(byte* address, byte bit) = 0;
private:
    void add_register_opcodes(const std::string& register_name, byte* register_address,
        byte base_value);

    std::function<void(byte*, byte)> _operation;
    bool _cb_prefix;
    std::map<std::string, std::vector<bitmask_opcode>> _bit_opcodes;

};

