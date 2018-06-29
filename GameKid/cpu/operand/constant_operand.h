#pragma once
#include <GameKid/cpu/operand.h>
#include <GameKid/cpu_types.h>

class constant_operand : public operand<byte>
{
public:
    byte value;
    explicit constant_operand(byte value) : value(value) {}

    std::string to_str(const byte* next) const override { return std::to_string(value); }

    byte load() const override { return value; }

    void store(byte value) override { throw "Cannot store"; }
};
