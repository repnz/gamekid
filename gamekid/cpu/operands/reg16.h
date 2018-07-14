#pragma once
#include <gamekid/cpu/operand.h>
#include <gamekid/utils/types.h>
#include <gamekid/cpu/reg.h>

namespace gamekid::cpu::operands {
    class reg16 : public operand<word>, public reg {
    private:
        byte* _low;
        byte* _high;
    public:
        reg16(std::string name, byte* low, byte* high) : reg(std::move(name), 2), _low(low), _high(high) {
        }


        word load_as_word() const override {
            return load();
        }

        word load() const override { return (*_high << 8) + *_low; }

        std::string to_str(const byte* next) const override { return name(); }

        void store(word value) override {
            *_low = (byte)(value & 0xFF);
            *_high = (byte)(value >> 8);
        }
    };
}