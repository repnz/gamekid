#pragma once
#include <string>
#include "GameKid/cpu_types.h"
#include <vector>
#include "GameKid/cpu.h"

class reg_mem_operand : public operand<byte>
{
private:
    memory & _mem;
    reg16& _reg;
public:
    
    reg16 & reg() { return _reg; }

    reg_mem_operand(memory& mem, reg16& reg) : _mem(mem), _reg(reg)
    {
    }

    byte load() const override
    {
        return _mem.load_byte(_reg.load());
    }

    void store(byte s) override
    {
        _mem.store<byte>(_reg.load(), s);
    }

    std::string to_str(byte* next) const override
    {
        return "[" + _reg.name() + "]";
    }
};

template <typename T>
std::vector<byte> immidiate_bytes(std::string operand)
{
    int parsed = stoi(operand);

    if (parsed > sizeof(T))
    {
        throw std::exception("Operand value exeeds");
    }

    T real_value = (T)parsed;

    std::vector<byte> v(sizeof(T));

    for (byte i = 0; i<sizeof(T); ++i)
    {
        v.push_back(real_value & 0xFF);
        real_value >>= 8;
    }

    return v;
}

template <typename T>
class imm_operand : public operand<T>
{
private:
    cpu & _cpu;

public:
    explicit imm_operand(cpu& cpu) : _cpu(cpu) {}

    T load() const override
    {
        return _cpu.mem.load<T>(_cpu.PC + 1);
    }

    void store(T value) override
    {
        throw "Cannot store";
    }

    std::string to_str(byte* next) const override
    {
        T item = *(T*)next;
        return std::to_string(item);
    }

    std::vector<byte> bytes(std::string operand) const override
    {
        return immidiate_bytes<T>(operand);
    }
};

template <typename move_type>
class imm_mem_operand : public operand<move_type>
{
private:
    cpu & _cpu;
public:
    explicit imm_mem_operand(cpu& cpu) : _cpu(cpu) {}

    word get_address() const
    {
        return _cpu.mem.load_word_le(_cpu.PC + 1);
    }

    move_type load() const override
    {
        return _cpu.mem.load<move_type>(get_address());
    }

    std::string to_str(byte* next) const override
    {
        const word address = *(word*)next;
        return std::to_string(address);
    }

    void store(move_type value) override
    {
        _cpu.mem.store<move_type>(get_address(), value);
    }

    std::vector<byte> bytes(std::string operand) const override
    {
        return immidiate_bytes<word>(operand);
    }
};

class reg16_with_offset : public operand<word>
{
private:
    cpu & _cpu;
    reg16& _reg16;
public:
    explicit reg16_with_offset(cpu& cpu, reg16& reg) : _cpu(cpu), _reg16(reg) {}

    reg16& reg() 
    {
        return _reg16;
    }

    word load() const override
    {
        const byte offset = _cpu.mem.load_byte(_cpu.PC + 1);

        if (offset <= CHAR_MAX)
        {
            return  _reg16.load() + offset;
        }

        return _reg16.load() - (offset - CHAR_MAX);
    }

    void store(word value) override
    {
        throw "Cannot store";
    }

    std::string to_str(byte* next) const override
    {
        const char value = *(char*)(next);

        if (value < 0)
        {
            return _reg16.name() + std::to_string(value);
        }

        return _reg16.name() + "+" + std::to_string(value);
    }

    std::vector<byte> bytes(std::string operand) const override
    {
        size_t index_of_offset = operand.find("+");
        std::string offset = operand.substr(index_of_offset + 1);
        return immidiate_bytes<word>(offset);
    }
};

class c_mem_operand : public operand<byte>
{
private:
    cpu & _cpu;
public:
    explicit c_mem_operand(cpu& cpu) : _cpu(cpu) {}

    byte load() const override
    {
        const word address = _cpu.C.load() + 0xFF00;
        return _cpu.mem.load_byte(address);
    }

    std::string to_str(byte* next) const override
    {
        return "[c]";
    }

    void store(byte value) override
    {
        const word address = _cpu.C.load() + 0xFF00;
        return _cpu.mem.store(address, value);
    }
};
