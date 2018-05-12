#include <GameKid/cpu/instructions/misc.h>
#include <GameKid/cpu/instructions/misc/swap.h>

void misc::add_instructions(instruction_set& set)
{
	set.add<swap_instruction>();
}
