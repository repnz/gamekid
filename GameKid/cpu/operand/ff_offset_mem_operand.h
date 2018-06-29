#pragma once
#include <GameKid/cpu/operand.h>
#include <GameKid/cpu.h>
#include <sstream>

class ff_offset_mem_operand : public operand<byte>
{
private:
    cpu & _cpu;
public:
    explicit ff_offset_mem_operand(cpu& cpu) : _cpu(cpu) {}

    word load_address() const
    {
        return _cpu.mem.load_byte(_cpu.PC + 1) + 0xFF00;
    }

    byte load() const override
    {
        return _cpu.mem.load_byte(load_address());
    }

    std::string to_str(const byte* next) const override
    {
        std::stringstream ss;
        ss << "[$FF" << std::uppercase << std::hex << *next << "]";
        return ss.str();
    }

    void store(byte value) override
    {
        return _cpu.mem.store(load_address(), value);
    }

    std::vector<byte> encode(const std::string& operand) const override
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