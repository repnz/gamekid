#pragma once
#include <string>
#include "GameKid/memory.h"
#include <vector>

class operand
{
public:
    virtual ~operand() = default;
    virtual std::string to_str(byte* next) const = 0;
    virtual std::vector<byte> bytes(std::string operand) const = 0;
};

template <typename T>
class source_operand : public operand
{
public:
    virtual T load() const = 0;
};

template <typename T>
class dest_operand : public operand
{
public:
    virtual void store(T value) = 0;
};

class reg8 : public source_operand<byte>, public dest_operand<byte>
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

    std::vector<byte> bytes(std::string operand) const override
    {
        return {};
    }

    byte* address()
    {
        return &_value;
    }
};

class reg16 : public source_operand<word>, public dest_operand<word>
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
    std::vector<byte> bytes(std::string operand) const override
    {
        return {};
    }
};