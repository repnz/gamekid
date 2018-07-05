#include "opcode.h"

using namespace gamekid::cpu;

opcode::opcode(cpu & cpu, const std::string & name, const std::vector<byte>& value, byte cycles)
    : _cpu(cpu), name(name), value(value), cycles(cycles) {
    if (name.size() == 0) {
        throw "Opcode name is empty";
    }
}

std::vector<byte> opcode::encode(const std::vector<std::string>& operands) const {
    return value;
}

std::string opcode::to_str(const byte * next) const {
    return name;
}

int opcode::size() const {
    return value.size();
}

int opcode::immidiate_size() const {
    return full_size() - size();
}

int opcode::full_size() const {
    return size();
}
