#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/alu_8.h>

instruction_set::instruction_set(cpu& cpu)
{
	instructions.push_back(std::make_unique<sub_instruction>(cpu));
}

std::unique_ptr<instruction>* instruction_set::get_instruction(const std::string& name)
{
	for (std::unique_ptr<::instruction>& current_instruction : instructions)
	{
		if (current_instruction->name == name)
		{
			return &current_instruction;
		}
	}

	return nullptr;
}

