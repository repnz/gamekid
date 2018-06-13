#pragma once
#include "GameKid/cpu/operand.h"

template <typename T>
class test_operand : public operand<T>
{
public:
    T value;

    explicit test_operand(T value) : value(value) { }

    std::string to_str(byte* next) const override { return std::to_string(value); }

    T load() const override { return value; }

    void store(T value) override { this->value = value; }
};
