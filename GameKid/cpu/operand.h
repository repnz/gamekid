#pragma once
#include <string>
#include "GameKid/memory/memory.h"
#include <vector>
#include "GameKid/utils/bits.h"

template <typename T>
class operand
{
public:
    virtual ~operand() = default;
    virtual std::string to_str(const byte* next) const = 0;
    
    virtual std::vector<byte> bytes(const std::string& operand) const
    {
        return {};
    }

    virtual T load() const = 0;
    virtual void store(T value) = 0;
    virtual int immidiate_size() const
    {
        return 0;
    }
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

    std::string to_str(const byte* next) const override
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
    enum {
        CARRY = 4,
        HALF_CARRY = 5,
        SUBSTRACT = 6,
        ZERO = 7
    };

    explicit flags_reg8()
        : reg8("F")
    {
    }
    
    bool check_bit(byte place) const
    {
        return bits::check_bit(_value, place);
    }

    void set_bit_on(byte place)
    {
        _value = bits::set_bit_on(_value, place);
    }

    void set_bit_off(byte place)
    {
        _value = bits::set_bit_off(_value, place);
    }

    void set_bit(byte place, bool is_on) 
    {
        _value = bits::set_bit(_value, place, is_on);
    }
    
    bool zero() const { return check_bit(ZERO); }
    bool substract() const { return check_bit(SUBSTRACT);}
    bool half_carry() const { return check_bit(HALF_CARRY); }
    bool carry() const { return check_bit(CARRY); }

    byte zero_bit() const { return zero() ? 1 : 0; }
    byte substract_bit() const { return substract() ? 1 : 0; }
    byte half_carry_bit() const { return half_carry() ? 1 : 0; }
    byte carry_bit() const { return carry() ? 1 : 0; }

    void zero(bool value) { set_bit(ZERO, value); }
    void substract(bool value) { set_bit(SUBSTRACT, value); }
    void half_carry(bool value) { set_bit(HALF_CARRY, value); }
    void carry(bool value) { set_bit(CARRY, value); }
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

    // non copyable
    reg16(const reg16&) = delete;
    reg16& operator=(reg16&) = delete;

    const std::string& name() const { return _name; }

    word load() const override
    {
        return (*_high << 8) + *_low;
    }

    std::string to_str(const byte* next) const override
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

    std::string to_str(const byte* next) const override
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

class reg16_addressing : public operand<word>
{
public:
    reg16 & reg;

    explicit reg16_addressing(reg16& reg) : reg(reg){}

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