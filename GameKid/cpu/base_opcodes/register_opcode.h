#pragma once
#include "GameKid/cpu/opcode.h"


struct register_opcode_values
{
    byte A;
    byte B;
    byte C;
    byte D;
    byte E;
    byte H;
    byte L;
};

class register_opcode : public opcode
{
private:
    std::function<void(byte* addr)> _operation;
public:
    reg _register;


    register_opcode(
        cpu& cpu,
        const std::string& name,
        const byte value,
        const std::function<void(byte* addr)>& operation,
        const reg& reg,
        bool cb_prefix,
        byte cycles
    )
        : opcode(cpu, name, value, cb_prefix, cycles),
        _operation(operation),
        _register(reg)
    {
    }

    void run() override
    {
        _operation(_register.address);
    }

    std::string to_str(byte* next) override
    {
        return name + " " + _register.name;
    }
};
