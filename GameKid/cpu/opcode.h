#pragma once

#include "GameKid/cpu_types.h"
#include "GameKid/cpu.h"

#include <string>
#include <vector>

class opcode {
protected:
    cpu & _cpu;
public:
    const std::string name;
    const std::vector<byte> value;
    const byte cycles;

    opcode(cpu& cpu, const std::string& name, const std::vector<byte>& value, byte cycles);

    virtual void run() = 0;
    virtual ~opcode() = default;

    virtual std::vector<byte> encode(const std::vector<std::string>& operands) const;
    
    virtual std::string to_str(const byte* next) const;
    
    int size() const;
    int immidiate_size() const;
    virtual int full_size() const;

};