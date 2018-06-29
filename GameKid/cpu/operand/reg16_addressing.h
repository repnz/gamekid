#pragma once
#include <GameKid/cpu/operand.h>
#include <GameKid/cpu_types.h>
#include "reg16.h"

class reg16_addressing : public operand<word>
{
public:
    reg16 & reg;

    explicit reg16_addressing(reg16& reg) : reg(reg) {}

    std::string to_str(const byte* next) const override
    {
        return "[" + reg.name() + "]";
    }

    word load() const override
    {
        return reg.load();
    }

    void store(word value) override
    {
        reg.store(value);
    }
};