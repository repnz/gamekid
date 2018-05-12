#include <GameKid/cpu/instructions/misc.h>
#include <GameKid/cpu/instructions/misc/swap.h>
#include "misc/scf.h"
#include "misc/ccf.h"

void misc::add_instructions(instruction_set& set)
{
	set.add<swap_instruction>();
	set.add<scf_instruction>();
	set.add<ccf_instruction>();
}
