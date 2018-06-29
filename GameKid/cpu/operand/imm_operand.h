#pragma once
#include <GameKid/cpu/operand.h>

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

    std::vector<byte> encode(const std::string& operand) const override
    {
        return bytes::little_endian_encode_str<T>(operand);
    }

    int immidiate_size() const override
    {
        return sizeof(T);
    }
};
