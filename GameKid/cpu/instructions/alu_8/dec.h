#pragma once
#include "GameKid/cpu/base_instructions/register_instruction.h"
#include "GameKid/opcodes.h"

class dec_instruction : public register_instruction
{
public:
	explicit dec_instruction(cpu& cpu);
	void run(byte* val) override;
};

inline dec_instruction::dec_instruction(cpu& cpu): register_instruction(cpu, "dec", false,
                                                                        DEC_A,
                                                                        DEC_B,
                                                                        DEC_C,
                                                                        DEC_D,
                                                                        DEC_E,
                                                                        DEC_H,
                                                                        DEC_L)
{
}

inline void dec_instruction::run(byte* val)
{
	_cpu.inc(val);
}
