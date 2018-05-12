#pragma once
#include <GameKid/opcodes.h>
#include <GameKid/cpu/base_instructions/bitmask_instruction.h>


class set_instruction : public bitmask_instruction
{
public:
	explicit set_instruction(cpu& cpu)
		: bitmask_instruction(cpu, "set",
			CB_SET_b_A,
			CB_SET_b_B,
			CB_SET_b_C,
			CB_SET_b_D,
			CB_SET_b_E,
			CB_SET_b_H,
			CB_SET_b_L,
			true)
	{
	}

	void run(byte* val, byte bit) override
	{
		_cpu.set(val, bit);
	}
};
