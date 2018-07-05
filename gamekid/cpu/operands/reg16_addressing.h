#pragma once
#include <gamekid/cpu/operand.h>
#include <gamekid/utils/types.h>
#include "reg16.h"

namespace gamekid::cpu::operands {
    class reg16_addressing : public operand<word> {
    public:
        reg16 & reg;

        explicit reg16_addressing(reg16& reg) : reg(reg) {}

        std::string to_str(const byte* next) const override {
            return "[" + reg.name() + "]";
        }

        word load() const override {
            return reg.load();
        }

        void store(word value) override {
            reg.store(value);
        }
    };
}