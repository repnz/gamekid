#include <gamekid/cpu/opcode_encoder.h>
#include <sstream>
#include <gamekid/utils/str.h>
#include <gamekid/cpu/instruction.h>

using namespace gamekid::cpu;

opcode_encoder::opcode_encoder(instruction_set& set) : _set(set) {
    for (instruction* ins : set.instructions()) {
        _instruction_map[ins->name] = ins;
    }
}

std::vector<byte> opcode_encoder::encode(const std::string& instruction) {
    std::vector<std::string> splitted = gamekid::utils::str::split(instruction, ' ');
    const auto& ins = _instruction_map.find(splitted[0]);

    if (ins == _instruction_map.end()) {
        return {};
    }

    return ins->second->encode(splitted);
}