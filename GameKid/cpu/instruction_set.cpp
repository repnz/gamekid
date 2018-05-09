#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/alu_8.h>

instruction_set::instruction_set(cpu& cpu)
{
	instructions.push_back(std::make_unique<sub_instruction>(cpu));
}

