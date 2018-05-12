#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/instructions/alu_8.h>
#include <GameKid/cpu/instructions/rotation.h>
#include <GameKid/cpu/instructions/bitmask.h>
#include <GameKid/cpu/instructions/misc.h>


instruction_set::instruction_set(cpu& cpu) : _cpu(cpu)
{
	// 8 bit arithmetic
	alu_8::add_instructions(*this);
	rotation::add_instructions(*this);
	bitmask::add_instructions(*this);
	misc::add_instructions(*this);
}

const std::vector<instruction*>& instruction_set::instructions()
{
	return _ptr_instructions;
}