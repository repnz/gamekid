#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/opcodes.h"

class sub_instruction : public register_instruction
{
public:
	explicit sub_instruction(cpu& cpu)
		: register_instruction(cpu, "sub", false,
			SUB_A_A, 
			SUB_A_B, 
			SUB_A_C,
			SUB_A_D,
			SUB_A_E, 
			SUB_A_H,
			SUB_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.sub(&_cpu.A, *val);
	}
};
