#pragma once
#include <GameKid/cpu/instruction_set.h>
#include <map>

class opcode_decoder
{
private:
    std::map<word, opcode*> _opcode_table;
    instruction_set & _set;
    void initialize_tables();
public:
    explicit opcode_decoder(instruction_set& set);
    opcode* decode(const byte* bytes);
};
