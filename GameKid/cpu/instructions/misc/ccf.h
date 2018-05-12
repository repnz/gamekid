#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"
#include "GameKid/opcodes.h"

class ccf_instruction : public single_opcode_instruction
{
public:
	ccf_instruction(cpu& cpu, const std::string& name)
		: single_opcode_instruction(cpu, name, CCF, false)
	{
	}

	void run() override
	{
		_cpu.ccf();
	}
};
