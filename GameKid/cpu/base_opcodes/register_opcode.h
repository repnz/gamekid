#pragma once
#include "GameKid/cpu/opcode.h"


class register_opcode : public opcode
{
private:
    std::function<void(byte* addr)> _operation;
public:
    std::string register_name;
    byte* register_address;


    register_opcode(
        cpu& cpu,
        const std::string& name,
        const byte value,
        const std::function<void(byte* addr)>& operation,
        const std::string& register_name,
        byte* register_address,
        bool cb_prefix,
        byte cycles
    )
        : opcode(cpu, name, value, cb_prefix, cycles),
        _operation(operation),
        register_name(register_name),
        register_address(register_address)
    {
    }

    void run() override
    {
        _operation(register_address);
    }

    std::string to_str(byte* next) override
    {
        return name + " " + register_name;
    }
};
