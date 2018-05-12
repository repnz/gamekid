#pragma once
#include "GameKid/opcodes.h"

class bit_instruction : public bitmask_instruction
{
public:
	explicit bit_instruction(cpu& cpu)
		: bitmask_instruction(cpu, "bit",
			CB_BIT_b_A,
			CB_BIT_b_B,
			CB_BIT_b_C,
			CB_BIT_b_D,
			CB_BIT_b_E,
			CB_BIT_b_H,
			CB_BIT_b_L,
			true)
	{
	}

	void run(byte* val, byte bit) override
	{
		_cpu.bit(*val, bit);
	}
};
