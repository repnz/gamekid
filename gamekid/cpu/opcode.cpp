#include "opcode.h"
#include <utility>

using namespace gamekid::cpu;

opcode::opcode(cpu & cpu, const std::string & name, std::vector<byte> value, byte cycles)
    : _cpu(cpu), name(name), value(std::move(value)), cycles(cycles) {
    if (name.empty()) {
        throw std::exception("Opcode name is empty");
    }
}

std::vector<byte> opcode::encode(const std::vector<std::string>& operands) const {
    return value;
}

std::string opcode::to_str(const byte * next) const {
    return name;
}

std::vector<byte> opcode::full_opcode(const byte* next) const {
    std::vector<byte> bytes = value;

    for (byte i=0; i<immidiate_size(); ++i) {
        bytes.emplace_back(next[i]);
    }

    return bytes;
}

size_t opcode::size() const {
    return value.size();
}

size_t opcode::immidiate_size() const {
    return full_size() - size();
}

size_t opcode::full_size() const {
    return size();
}
