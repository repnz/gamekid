#include <GameKid/cpu/instructions/rotation.h>
#include <GameKid/cpu/instructions/rotation/srl.h>
#include <GameKid/cpu/instructions/rotation/rla.h>
#include <GameKid/cpu/instructions/rotation/rrc.h>
#include <GameKid/cpu/instructions/rotation/rrca.h>
#include <GameKid/cpu/instructions/rotation/sla.h>
#include <GameKid/cpu/instructions/rotation/rr.h>
#include <GameKid/cpu/instructions/rotation/rl.h>
#include <GameKid/cpu/instructions/rotation/rra.h>
#include <GameKid/cpu/instructions/rotation/rlca.h>
#include <GameKid/cpu/instructions/rotation/rlc.h>
#include <GameKid/cpu/instructions/rotation/sra.h>

void rotation::add_instructions(instruction_set & set)
{
	set.add<rlca_instruction>();
	set.add<rla_instruction>();
	set.add<rrca_instruction>();
	set.add<rra_instruction>();
	set.add<rlc_instruction>();
	set.add<rl_instruction>();
	set.add<rrc_instruction>();
	set.add<rr_instruction>();
	set.add<sla_instruction>();
	set.add<sra_instruction>();
	set.add<srl_instruction>();
}
