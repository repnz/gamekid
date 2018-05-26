#pragma once
#include <GameKid/cpu/opcode.h>

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

class memory_move_operand : public source_operand, public dest_operand
{
public:
    memory& _mem;
    reg16 _reg;

    memory_move_operand(memory& mem, const reg16& reg) : _mem(mem), _reg(reg)
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

class immidiate_move_operand : public source_operand
{
private:
    cpu & _cpu;

public:
    explicit immidiate_move_operand(cpu& cpu) : _cpu(cpu){}

    byte load() override
    {
        return _cpu.mem.load_byte(_cpu.PC + 1);
    }

    std::string to_str(byte* next) override
    {
        return std::to_string(*next);
    }
};

class immidiate_mem_operand : public source_operand, public dest_operand
{
private:
    cpu & _cpu;
public:
    explicit immidiate_mem_operand(cpu& cpu) : _cpu(cpu){}

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

template <typename TSource, typename TDestination>
//    requires source_operand && dest_operand
class move_opcode : public opcode
{

private:
    TSource _src;
    TDestination _dst;
public:
    move_opcode(cpu& cpu, byte value, byte cycles, const TSource& src, const TDestination& dst) :
    opcode(cpu, "ld", value, false, cycles), _src(src), _dst(dst)
    {
    }

    void run() override
    {
        byte moved_byte = _src.load();
        _dst.store(moved_byte);
    }

    std::string to_str(byte* next) override
    {
        return "ld " + _dst.to_str(next) + ", " + _src.to_str(next);
    }
};