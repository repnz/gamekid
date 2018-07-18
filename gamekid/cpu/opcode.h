#pragma once

#include "gamekid/utils/types.h"
#include "gamekid/cpu/cpu.h"

#include <string>
#include <vector>

namespace gamekid::cpu {
    class opcode {
    protected:
        cpu & _cpu;
    public:
        const std::string name;
        const std::vector<byte> value;
        const byte cycles;

        opcode(cpu& cpu, const std::string& name, std::vector<byte> value, byte cycles);

        virtual void run() = 0;
        virtual ~opcode() = default;

        virtual std::vector<byte> encode(const std::vector<std::string>& operands) const;

        virtual std::string to_str(const byte* next) const;

        std::vector<byte> full_opcode(const byte* next) const;

        byte size() const;
        byte immidiate_size() const;
        virtual byte full_size() const;
    };
}