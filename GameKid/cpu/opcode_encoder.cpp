#include <GameKid/cpu/opcode_encoder.h>
#include <sstream>
#include <GameKid/cpu/instruction.h>

opcode_encoder::opcode_encoder(instruction_set& set) : _set(set)
{
    for (instruction* ins : set.instructions())
    {
        _instruction_map[ins->name] = ins;
    }
}

std::vector<byte> opcode_encoder::encode(const std::string& instruction)
{
    std::vector<std::string> splitted = string_tools::split(instruction, ' ');
    const auto& ins = _instruction_map.find(splitted[0]);

    if (ins == _instruction_map.end())
    {
        return {};
    }

    return ins->second->parse(splitted);
}