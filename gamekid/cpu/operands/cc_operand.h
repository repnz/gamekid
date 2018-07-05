#pragma once
#include <gamekid/cpu/operand.h>
#include <gamekid/cpu/operands/flags_reg8.h>

namespace gamekid::cpu::operands {
    class cc_operand : public operand<bool>
    {
    private:
        const flags_reg8& _reg;
        const byte _flag_place;
        std::string _name;
        const bool _value;
    public:
        explicit cc_operand(const flags_reg8& reg, const byte flag_place, const std::string& name, bool value) :
            _reg(reg), _flag_place(flag_place), _name(name), _value(value)
        {
        }

        std::string to_str(const byte* next) const override {
            return _name;
        }

        bool load() const override {
            return _reg.check_bit(_flag_place) == _value;
        }

        void store(bool value) override {
            throw "Cannot store";
        }
    };
}