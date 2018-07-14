#pragma once
#include <gamekid/cpu/operand.h>
#include <gamekid/cpu/reg.h>

namespace gamekid::cpu::operands {

    class reg8 : public operand<byte>, public reg {
    protected:
        byte _value;
    public:
        explicit reg8(const std::string& name) : reg(name, 1), _value(0) {}

        // non copyable
        reg8(const reg8&) = delete;
        reg8& operator=(const reg8&) = delete;


        byte load() const override { return _value; }

        void store(byte new_value) override { _value = new_value; }

        std::string to_str(const byte* next) const override { return name(); }

        word load_as_word() const override { return load(); }

        byte* address() { return &_value; }
    };
}
