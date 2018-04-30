#include "pch.h"
#include <GameKid/cpu.h>


TEST(Commands, RL_n) {
	cpu c;
	byte val = 1<<7; 
	c.rl_n(&val, 1);
	ASSERT_EQ(val, 1) << "bit 7 did not move to place 0";
	ASSERT_EQ(c.carry_flag, 1) << "carry flag did not update correctly";
}