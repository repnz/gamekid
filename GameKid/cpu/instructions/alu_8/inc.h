#pragma once
#include "GameKid/cpu.h"
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class inc_instruction : public register_instruction
{
public:
	explicit inc_instruction(cpu& cpu);
	void run(byte* val) override;
};

inline inc_instruction::inc_instruction(cpu& cpu) : register_instruction(cpu, "inc", false,
	INC_A,
	INC_B,
	INC_C,
	INC_D,
	INC_E,
	INC_H,
	INC_L)
{
}

inline void inc_instruction::run(byte* val)
{
	_cpu.inc(val);
}
