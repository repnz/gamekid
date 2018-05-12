#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/instructions/bitmask.h>
#include <GameKid/cpu/instructions/bitmask/set.h>
#include <GameKid/cpu/instructions/bitmask/res.h>
#include <GameKid/cpu/instructions/bitmask/bit.h>

inline void bitmask::add_instructions(instruction_set& set)
{
    set.add<bit_instruction>();
    set.add<res_instruction>();
    set.add<set_instruction>();
}
