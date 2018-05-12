#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"
#include "GameKid/opcodes.h"

class ccf_instruction : public single_opcode_instruction
{
public:
	explicit ccf_instruction(cpu& cpu)
		: single_opcode_instruction(cpu, "ccf", CCF, false, 4)
	{
	}

	void run() override
	{
		_cpu.ccf();
	}
};
