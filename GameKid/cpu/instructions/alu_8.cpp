#include <GameKid/cpu/instructions/alu_8.h>
#include <GameKid/cpu/instructions/alu_8/inc.h>
#include <GameKid/cpu/instructions/alu_8/or.h>
#include <GameKid/cpu/instructions/alu_8/xor.h>
#include <GameKid/cpu/instructions/alu_8/and.h>
#include <GameKid/cpu/instructions/alu_8/dec.h>
#include <GameKid/cpu/instructions/alu_8/cp.h>
#include <GameKid/cpu/instructions/alu_8/adc.h>
#include <GameKid/cpu/instructions/alu_8/sbc.h>
#include <GameKid/cpu/instructions/alu_8/add.h>
#include <GameKid/cpu/instructions/alu_8/sub.h>

void alu_8::add_instructions(instruction_set & set)
{
    set.add<add_instruction>();
    set.add<adc_instruction>();
    set.add<sub_instruction>();
    set.add<sbc_instruction>();
    set.add<xor_instruction>();
    set.add<or_instruction>();
    set.add<and_instruction>();
    set.add<cp_instruction>();
    set.add<inc_instruction>();
    set.add<dec_instruction>();
}
