#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/alu_8.h>


instruction_set::instruction_set(cpu& cpu)
{
	_instructions.push_back(std::make_unique<sub_instruction>(cpu));

	for (std::unique_ptr<instruction>& ptr : _instructions)
	{
		_ptr_instructions.push_back(ptr.get());
	}
}

const std::vector<instruction*>& instruction_set::instructions()
{
	return _ptr_instructions;
}