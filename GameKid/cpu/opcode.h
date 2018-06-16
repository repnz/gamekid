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
    const std::string name;
    const std::vector<byte> value;
    const byte cycles;

    opcode(cpu& cpu, const std::string& name, const std::vector<byte>& value, byte cycles)
        : _cpu(cpu), name(name), value(value), cycles(cycles)
    {
        if (name.size() == 0)
        {
            throw "Opcode name is empty";
        }
    }

    virtual std::vector<byte> bytes(const std::vector<std::string>& operands) const
    {
        return bytes();
    }

    virtual std::vector<byte> bytes() const
    {
        return value;
    }

    virtual std::string to_str(const byte* next) const
    {
        return name;
    }

    virtual void run() = 0;
    virtual ~opcode() = default;
    
    int size() const
    {
        return value.size();
    }

    virtual int full_size() const
    {
        return size();
    }

};