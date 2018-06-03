#pragma once
#include <string>
#include "GameKid/memory.h"
#include <vector>

template <typename T>
class operand
{
public:
    virtual ~operand() = default;
    virtual std::string to_str(byte* next) const = 0;
    
    virtual std::vector<byte> bytes(std::string operand) const
    {
        return {};
    }

    virtual T load() const = 0;
    virtual void store(T value) = 0;
};


class reg8 : public operand<byte>
{
private:
    std::string _name;
    byte _value;
public:
    
    explicit reg8(const std::string& name) : _name(name), _value(0) {}
    
    const std::string& name() const
    {
        return _name;
    }

    // non copyable
    reg8(const reg8&) = delete;
    reg8& operator=(const reg8&) = delete;


    byte load() const override 
    {
        return _value;
    }

    std::string to_str(byte* next) const override
    {
        return _name;
    }

    void store(byte new_value) override
    {
        _value = new_value;
    }

    byte* address()
    {
        return &_value;
    }
};

class reg16 : public operand<word>
{
private:
    std::string _name;
    byte* _low;
    byte* _high;
public:
    reg16(const std::string& name, byte* low, byte* high) :
        _name(name), _low(low), _high(high) {}

    reg16(const reg16&) = delete;
    reg16& operator=(reg16&) = delete;

    const std::string& name() const { return _name; }

    word load() const override
    {
        return (*_high << 8) + *_low;
    }

    std::string to_str(byte* next) const override
    {
        return _name;
    }

    void store(word value) override
    {
        *_low = (byte)(value & 0xFF);
        *_high = (byte)(value >> 8);
    }
};

class constant_operand : public operand<byte>
{
public:
    byte value;
    explicit constant_operand(byte value) : value(value){}
    
    std::string to_str(byte* next) const override
    {
        return std::to_string(value);
    }

    byte load() const override
    {
        return value;
    }

    void store(byte value) override
    {
        throw "Cannot store";
    }
};