#pragma once
#include <GameKid/cpu/instruction_set.h>
#include <map>

class opcode_decoder
{
private:
    std::map<byte, opcode*> _main_table;
    std::map<byte, opcode*> _cb_prefix_table;
    instruction_set & _set;
    void initialize_tables();
public:
    explicit opcode_decoder(instruction_set& set);
    opcode* decode(const byte* bytes);
};
