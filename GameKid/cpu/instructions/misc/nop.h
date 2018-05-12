#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"
#include "GameKid/opcodes.h"

class nop_instruction : public single_opcode_instruction
{
public:
	explicit nop_instruction(cpu& cpu)
		: single_opcode_instruction(cpu, "nop", NOP, false, 4)
	{
	}

	void run() override
	{
		// do nothing 
	}
};
