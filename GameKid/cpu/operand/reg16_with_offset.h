#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu/operand.h>
#include "reg16.h"
#include <GameKid/utils/bytes.h>

class reg16_with_offset : public operand<word>
{
private:
    cpu & _cpu;
    reg16& _reg16;
public:
    explicit reg16_with_offset(cpu& cpu, reg16& reg) : _cpu(cpu), _reg16(reg) {}

    reg16& reg(){
        return _reg16;
    }

    word load() const override {
        const byte offset = _cpu.mem.load_byte(_cpu.PC + 1);

        if (offset <= CHAR_MAX) {
            return  _reg16.load() + offset;
        }

        return _reg16.load() - (offset - CHAR_MAX);
    }

    void store(word value) override { throw "Cannot store"; }

    std::string to_str(const byte* next) const override {
        const char value = *(char*)(next);

        if (value < 0) {
            return _reg16.name() + std::to_string(value);
        }

        return _reg16.name() + "+" + std::to_string(value);
    }

    std::vector<byte> encode(const std::string& operand) const override {
        size_t index_of_offset = operand.find("+");
        std::string offset = operand.substr(index_of_offset + 1);
        return bytes::little_endian_encode_str<byte>(offset);
    }

    int immidiate_size() const override { return 1; }
};