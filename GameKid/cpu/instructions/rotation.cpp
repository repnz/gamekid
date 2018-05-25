#include <GameKid/cpu/instructions/rotation.h>
#include "rotation/srl.h"
#include "rotation/rla.h"
#include "rotation/rrc.h"
#include "rotation/rrca.h"
#include "rotation/sla.h"
#include "rotation/rr.h"
#include "rotation/rl.h"
#include "rotation/rra.h"
#include "rotation/rlca.h"
#include "rotation/rlc.h"
#include "rotation/sra.h"

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
