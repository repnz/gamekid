#pragma once
#include "GameKid/cpu_types.h"
#include "GameKid/opcodes.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"


class rlc_instruction : public register_instruction
{
public:
	explicit rlc_instruction(cpu& cpu)
		: register_instruction(cpu, "rlc", true,
			CB_RLC_A,
			CB_RLC_B,
			CB_RLC_C,
			CB_RLC_D,
			CB_RLC_E,
			CB_RLC_H,
			CB_RLC_L)
	{
	}

	void run(byte* val) override
	{
		_cpu.rlc(val);
	}
};
