#include <GameKid/cpu/instruction_set.h>
#include "bitmask.h"
#include "bitmask/set.h"
#include "bitmask/res.h"
#include "bitmask/bit.h"

inline void bitmask::add_instructions(instruction_set& set)
{
    set.add<bit_instruction>();
    set.add<res_instruction>();
    set.add<set_instruction>();
}
