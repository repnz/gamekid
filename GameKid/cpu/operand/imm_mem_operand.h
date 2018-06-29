#pragma once
#include <GameKid/cpu/operand.h>

template <typename T>
class imm_mem_operand : public operand<T>
{
private:
    cpu & _cpu;
public:
    explicit imm_mem_operand(cpu& cpu) : _cpu(cpu) {}

    word get_address() const
    {
        return _cpu.mem.load_word(_cpu.PC + 1);
    }

    T load() const override
    {
        return _cpu.mem.load<T>(get_address());
    }

    std::string to_str(const byte* next) const override
    {
        const word address = *(word*)next;
        return std::to_string(address);
    }

    void store(T value) override
    {
        _cpu.mem.store<T>(get_address(), value);
    }

    std::vector<byte> encode(const std::string& operand) const override
    {
        return bytes::little_endian_encode_str<word>(operand);
    }

    int immidiate_size() const override
    {
        return sizeof(word); // the address
    }
};
