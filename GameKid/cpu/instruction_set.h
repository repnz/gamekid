#pragma once
#include <vector>
#include <GameKid/cpu/instruction.h>


class instruction_set
{
	std::vector<std::unique_ptr<instruction>> instructions;

	instruction_set();
};
