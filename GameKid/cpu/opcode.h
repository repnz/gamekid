#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu.h"
#include <vector>


class opcode
{
protected:
    cpu & _cpu;
public:
    std::string name;
    byte value;
    bool cb_prefix;
    byte cycles;

    opcode(cpu& cpu, const std::string& name, byte value, bool cb_prefix, byte cycles)
        : _cpu(cpu), name(name), value(value), cb_prefix(cb_prefix), cycles(cycles)
    {
    }

    virtual std::vector<byte> bytes(const std::vector<std::string>& operands)
    {
        return bytes();
    }

    virtual std::vector<byte> bytes()
    {
        if (cb_prefix)
        {
            return { 0xCB, value };
        }

        return { value };
    }

    virtual std::string to_str(byte* next)
    {
        return name;
    }

    virtual void run() = 0;
    virtual ~opcode() = default;
};