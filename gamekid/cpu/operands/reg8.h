#pragma once
#include <gamekid/cpu/operand.h>

namespace gamekid::cpu::operands {

    class reg8 : public operand<byte> {
    protected:
        std::string _name;
        byte _value;
    public:
        explicit reg8(const std::string& name) : _name(name), _value(0) {}

        const std::string& name() const {
            return _name;
        }

        // non copyable
        reg8(const reg8&) = delete;
        reg8& operator=(const reg8&) = delete;


        byte load() const override { return _value; }

        void store(byte new_value) override { _value = new_value; }

        std::string to_str(const byte* next) const override { return _name; }

        byte* address() { return &_value; }
    };
}