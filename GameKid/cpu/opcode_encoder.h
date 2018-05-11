#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include <vector>
#include "instruction_set.h"

class opcode_encoder
{
private:
	instruction_set & _set;
	std::map<std::string, instruction*> _instruction_map;
public:
	opcode_encoder(instruction_set& set);
	std::vector<byte> encode(const std::string& instruction);
};
