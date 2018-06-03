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
protected:
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

class flags_reg8 : public reg8
{
public:
    explicit flags_reg8()
        : reg8("F")
    {
    }
    
    bool check_bit(byte place)
    {
        return _value & (1 << place);
    }

    void set_bit_on(byte place)
    {
        _value |= (1 << place);
    }

    void set_bit_off(byte place)
    {
        _value &= ~(1 << place);
    }

    void set_bit(byte place, bool is_on)
    {
        if (is_on) { set_bit_on(place); }
        else { set_bit_off(place); }
    }

    bool zero() { return check_bit(7); }
    bool substract() { return check_bit(6);}
    bool half_carry() { return check_bit(5); }
    bool carry() { return check_bit(4); }

    byte zero_bit() { return zero() ? 1 : 0; }
    byte substract_bit() { return substract() ? 1 : 0; }
    byte half_carry_bit() { return half_carry() ? 1 : 0; }
    byte carry_bit() { return carry() ? 1 : 0; }

    void zero(bool value) { set_bit(7, value); }
    void substract(bool value) { set_bit(6, value); }
    void half_carry(bool value) { set_bit(5, value); }
    void carry(bool value) { set_bit(4, value); }


    flags_reg8(const flags_reg8&) = delete;
    flags_reg8& operator=(const flags_reg8&) = delete;
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