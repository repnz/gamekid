#pragma once
#include <string>
#include "GameKid/memory.h"
#include "GameKid/cpu.h"

class source_operand
{
public:
    virtual ~source_operand() = default;
    virtual byte load() = 0;
    virtual std::string to_str(byte* next) = 0;
};

class dest_operand
{
public:
    virtual ~dest_operand() = default;
    virtual void store(byte value) = 0;
    virtual std::string to_str(byte* next) = 0;
};


class reg_mem_operand : public source_operand, public dest_operand
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

class imm_operand : public source_operand
{
private:
    cpu & _cpu;

public:
    explicit imm_operand(cpu& cpu) : _cpu(cpu) {}

    byte load() override
    {
        return _cpu.mem.load_byte(_cpu.PC + 1);
    }

    std::string to_str(byte* next) override
    {
        return std::to_string(*next);
    }
};

class imm_mem_operand : public source_operand, public dest_operand
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

class reg_operand : public source_operand, public dest_operand
{
private:
    reg8 _reg;
public:
    reg_operand(const reg8& reg) : _reg(reg) {}

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

class c_mem_operand : public source_operand, public dest_operand
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
