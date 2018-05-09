#pragma once
#include <vector>
#include <GameKid/cpu/instruction.h>
#include <memory>


class instruction_set
{
public:
	std::vector<std::unique_ptr<instruction>> instructions;
	instruction_set(cpu& cpu);
	std::unique_ptr<instruction>* get_instruction(const std::string& name);
	
};
