#include "alu_8.h"
#include "alu_8/inc.h"
#include "alu_8/or.h"
#include "alu_8/xor.h"
#include "alu_8/and.h"
#include "alu_8/dec.h"
#include "alu_8/cp.h"
#include "alu_8/adc.h"
#include "alu_8/sbc.h"
#include "alu_8/add.h"
#include "alu_8/sub.h"

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
