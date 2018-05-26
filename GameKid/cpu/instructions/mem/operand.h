#pragma once
#include <string>
#include "GameKid/memory.h"
#include "GameKid/cpu.h"

template <typename T>
class source_operand
{
public:
    virtual ~source_operand() = default;
    virtual T load() = 0;
    virtual std::string to_str(byte* next) = 0;
};

template <typename T>
class dest_operand
{
public:
    virtual ~dest_operand() = default;
    virtual void store(T value) = 0;
    virtual std::string to_str(byte* next) = 0;
};

class reg_mem_operand : public source_operand<byte>, public dest_operand<byte>
{
public:
    memory & _mem;
    reg16 _reg;

    reg_mem_operand(memory& mem, const reg16& reg) : _mem(mem), _reg(reg)
    {
    }


    byte load() override
    {
        return _mem.load_byte(_reg.get());
    }

    void store(byte s) override
    {
        _mem.store(_reg.get(), s);
    }

    std::string to_str(byte* next) override
    {
        return "[" + _reg.name + "]";
    }
};

template <typename T>
class imm_operand : public source_operand<T>
{
private:
    cpu & _cpu;

public:
    explicit imm_operand(cpu& cpu) : _cpu(cpu) {}

    T load() override
    {
        return _cpu.mem.load<T>(_cpu.PC + 1);
    }

    std::string to_str(byte* next) override
    {
        return std::to_string(*next);
    }
};

class imm_mem_operand : public source_operand<byte>, public dest_operand<byte>
{
private:
    cpu & _cpu;
public:
    explicit imm_mem_operand(cpu& cpu) : _cpu(cpu) {}

    byte load() override
    {
        const word address = _cpu.mem.load_word_le(_cpu.PC + 1);
        return _cpu.mem.load_byte(address);
    }

    std::string to_str(byte* next) override
    {
        const word address = *(word*)next;
        return std::to_string(address);
    }

    void store(byte value) override
    {
        const word address = _cpu.mem.load_word_le(_cpu.PC + 1);
        _cpu.mem.store(address, value);
    }
};

class reg8_operand : public source_operand<byte>, public dest_operand<byte>
{
private:
    reg8 _reg;
public:
    reg8_operand(const reg8& reg) : _reg(reg) {}

    byte load() override
    {
        return _reg.get();
    }

    std::string to_str(byte* next) override
    {
        return _reg.name;
    }

    void store(byte value) override
    {
        _reg.set(value);
    }
};

class reg16_operand : public source_operand<word>, public dest_operand<word>
{
private:
    reg16 _reg;
public:
    reg16_operand(const reg16& reg) : _reg(reg) {}

    word load() override
    {
        return _reg.get();
    }

    std::string to_str(byte* next) override
    {
        return _reg.name;
    }

    void store(word value) override
    {
        _reg.set(value);
    }
};

class c_mem_operand : public source_operand<byte>, public dest_operand<byte>
{
private:
    cpu & _cpu;
public:
    explicit c_mem_operand(cpu& cpu);

    byte load() override
    {
        const word address = _cpu.regs.C.get() + 0xFF00;
        return _cpu.mem.load_byte(address);
    }

    std::string to_str(byte* next) override
    {
        return "[c]";
    }

    void store(byte value) override
    {
        const word address = _cpu.regs.C.get() + 0xFF00;
        return _cpu.mem.store(address, value);
    }
};
