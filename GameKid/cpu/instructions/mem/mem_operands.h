#pragma once
#include <string>
#include "GameKid/cpu_types.h"
#include <vector>
#include "GameKid/cpu.h"
#include <sstream>

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

    std::string to_str(const byte* next) const override
    {
        return "[" + _reg.name() + "]";
    }
};

std::vector<byte> immidiate_bytes(const std::string& operand, int size_in_bytes);

template <typename T>
std::vector<byte> immidiate_bytes(const std::string& operand)
{
    return immidiate_bytes(operand, sizeof(T));
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

    std::string to_str(const byte* next) const override
    {
        T item = *(T*)next;
        return std::to_string(item);
    }

    std::vector<byte> bytes(const std::string& operand) const override
    {
        return immidiate_bytes<T>(operand);
    }

    int immidiate_size() const override
    {
        return sizeof(T);
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

    std::string to_str(const byte* next) const override
    {
        const word address = *(word*)next;
        return std::to_string(address);
    }

    void store(move_type value) override
    {
        _cpu.mem.store<move_type>(get_address(), value);
    }

    std::vector<byte> bytes(const std::string& operand) const override
    {
        return immidiate_bytes<word>(operand);
    }

    int immidiate_size() const override
    {
        return sizeof(move_type);
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

    std::string to_str(const byte* next) const override
    {
        const char value = *(char*)(next);

        if (value < 0)
        {
            return _reg16.name() + std::to_string(value);
        }

        return _reg16.name() + "+" + std::to_string(value);
    }

    std::vector<byte> bytes(const std::string& operand) const override
    {
        size_t index_of_offset = operand.find("+");
        std::string offset = operand.substr(index_of_offset + 1);
        return immidiate_bytes<word>(offset);
    }

    int immidiate_size() const override
    {
        return 1;
    }
};

class ff_offset_mem_operand : public operand<byte>
{
private:
    cpu & _cpu;
public:
    explicit ff_offset_mem_operand(cpu& cpu) : _cpu(cpu) {}

    word load_address() const
    {
        return _cpu.mem.load_byte(_cpu.PC+1) + 0xFF00;
    }

    byte load() const override
    {
        return _cpu.mem.load_byte(load_address());
    }

    std::string to_str(const byte* next) const override
    {
        std::stringstream ss;
        ss << "[$FF" << std::uppercase << std::hex <<  *next << "]";
        return ss.str();
    }

    void store(byte value) override
    {
        return _cpu.mem.store(load_address(), value);
    }

    std::vector<byte> bytes(const std::string& operand) const override
    {
        int value = std::stoi(operand);

        if (value < -128 || value >= 128)
        {
            throw "Error";
        }

        return { static_cast<byte>(value) };
    }
    
    int immidiate_size() const override
    {
        return 1;
    }
};

class c_mem_operand : public operand<byte>
{
private:
    cpu & _cpu;
public:
    explicit c_mem_operand(cpu& cpu) : _cpu(cpu) {}

    word load_address() const
    {
        return _cpu.C.load() + 0xFF00;
    }

    byte load() const override
    {
        return _cpu.mem.load_byte(load_address());
    }

    std::string to_str(const byte* next) const override
    {
        return "[c]";
    }

    void store(byte value) override
    {
        return _cpu.mem.store(load_address(), value);
    }
};

class op_reg_mem_operand : public operand<byte>
{
private:
    memory & _mem;
    reg16& _reg;
public:

    reg16 & reg() { return _reg; }

    op_reg_mem_operand(memory& mem, reg16& reg) : _mem(mem), _reg(reg)
    {
    }

    virtual word change(word original) const = 0;

    byte load() const override
    {
        const word original_address = _reg.load();
        _reg.store(change(original_address));
        return _mem.load_byte(original_address);
    }

    void store(byte s) override
    {
        const word new_address = _reg.load();
        _reg.store(change(new_address));
        _mem.store<byte>(new_address, s);
    }

    std::string to_str(const byte* next) const override
    {
        return "[" + _reg.name() + "]";
    }
};

class inc_reg_mem_operand : public op_reg_mem_operand
{
public:
    inc_reg_mem_operand(memory& mem, reg16& reg)
        : op_reg_mem_operand(mem, reg)
    {
    }

    word change(word original) const override { return original + 1; }
};

class dec_reg_mem_operand : public op_reg_mem_operand
{
public:
    dec_reg_mem_operand(memory& mem, reg16& reg)
        : op_reg_mem_operand(mem, reg)
    {
    }

    word change(word original) const override { return original - 1; }
};