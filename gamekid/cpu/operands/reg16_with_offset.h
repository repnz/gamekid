#pragma once
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/operand.h>
#include "reg16.h"
#include <gamekid/utils/bytes.h>
#include <gamekid/system.h>

namespace gamekid::cpu::operands {
    class reg16_with_offset : public operand<word>
    {
    private:
        system & _system;
        reg16& _reg16;
    public:
        explicit reg16_with_offset(system& system, reg16& reg) : _system(system), _reg16(reg) {}

        reg16& reg() {
            return _reg16;
        }

        word load() const override;

        void store(word value) override { throw "Cannot store"; }

        std::string to_str(const byte* next) const override;

        std::vector<byte> encode(const std::string& operand) const override;

        int immidiate_size() const override;
    };
}