#pragma once
#include <GameKid/cpu/operand.h>
#include <GameKid/cpu_types.h>

class reg16 : public operand<word>
{
private:
    std::string _name;
    byte* _low;
    byte* _high;
public:
    reg16(const std::string& name, byte* low, byte* high) :
        _name(name), _low(low), _high(high) {}

    const std::string& name() const { return _name; }

    word load() const override { return (*_high << 8) + *_low; }

    std::string to_str(const byte* next) const override { return _name; }

    void store(word value) override
    {
        *_low = (byte)(value & 0xFF);
        *_high = (byte)(value >> 8);
    }
};