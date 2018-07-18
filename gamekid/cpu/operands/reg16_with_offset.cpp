#include "reg16_with_offset.h"

using gamekid::cpu::operands::reg16_with_offset;

word reg16_with_offset::load() const {

    const byte offset = _system.cpu().immidiate<byte>();

    if (offset <= CHAR_MAX) {
        return  _reg16.load() + offset;
    }

    return _reg16.load() - (offset - CHAR_MAX);
}

std::string reg16_with_offset::to_str(const byte* next) const  {
    const char value = *(char*)(next);

    if (value < 0) {
        return _reg16.name() + std::to_string(value);
    }

    return _reg16.name() + "+" + std::to_string(value);
}

std::vector<byte> reg16_with_offset::encode(const std::string& operand) const {
    size_t index_of_offset = operand.find('+');
    std::string offset = operand.substr(index_of_offset + 1);
    return gamekid::utils::bytes::little_endian_encode_str<byte>(offset);
}

int reg16_with_offset::immidiate_size() const {
    return 1;
}