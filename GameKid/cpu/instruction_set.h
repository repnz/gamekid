#pragma once
#include <vector>
#include <GameKid/cpu/instruction.h>
#include <memory>


class instruction_set
{
	std::vector<std::unique_ptr<instruction>> _instructions;
	std::vector<instruction*> _ptr_instructions;
public:
	const std::vector<instruction*>& instructions();
	explicit instruction_set(cpu& cpu);

};
