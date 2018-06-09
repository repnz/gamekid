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
    std::vector<byte> value;
    byte cycles;

    opcode(cpu& cpu, const std::string& name, std::vector<byte> value, byte cycles)
        : _cpu(cpu), name(name), value(value), cycles(cycles)
    {
        if (name.size() == 0)
        {
            throw "Opcode name is empty";
        }
    }

    virtual std::vector<byte> bytes(const std::vector<std::string>& operands)
    {
        return bytes();
    }

    virtual std::vector<byte> bytes()
    {
        return value;
    }

    virtual std::string to_str(byte* next)
    {
        return name;
    }

    virtual void run() = 0;
    virtual ~opcode() = default;
    
    virtual int size()
    {
        return value.size();
    }

};