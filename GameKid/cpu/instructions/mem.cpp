#include "mem.h"
#include "mem/ld.h"

void mem::add_instructions(instruction_set & set)
{
    set.add<ld_instruction>();
}
