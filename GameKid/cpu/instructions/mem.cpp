#include "mem.h"
#include "mem/ld.h"
#include <GameKid/cpu/instruction_set.h>

void mem::initialize()
{
    _set.add_instruction(std::make_unique<ld_instruction>(_cpu));
}
