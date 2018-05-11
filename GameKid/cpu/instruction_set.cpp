#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/alu_8.h>


instruction_set::instruction_set(cpu& cpu) : _cpu(cpu)
{
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
}

const std::vector<instruction*>& instruction_set::instructions()
{
	return _ptr_instructions;
}