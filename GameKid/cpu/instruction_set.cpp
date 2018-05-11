#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/alu_8.h>
#include "rotates.h"


instruction_set::instruction_set(cpu& cpu) : _cpu(cpu)
{
	// 8 bit arithmetic
	add<add_instruction>();
	add<adc_instruction>();
	add<sub_instruction>();
	add<sbc_instruction>();
	add<xor_instruction>();
	add<or_instruction>();
	add<and_instruction>();
	add<cp_instruction>();
	add<inc_instruction>();
	add<dec_instruction>();

	// rotation 
	add<rlca_instruction>();
	add<rla_instruction>();
	add<rrca_instruction>();
	add<rra_instruction>();
	add<rlc_instruction>();
	add<rl_instruction>();
	add<rrc_instruction>();
	add<rr_instruction>();
	add<sla_instruction>();
	add<sra_instruction>();
	add<srl_instruction>();

}

const std::vector<instruction*>& instruction_set::instructions()
{
	return _ptr_instructions;
}