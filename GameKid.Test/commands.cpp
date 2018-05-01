#include "pch.h"
#include <GameKid/cpu.h>


TEST(Commands, RL_1) 
{
	cpu c = { 0 };
	byte val = 1<<7; 
	c.rl_n(&val, 1);
	ASSERT_EQ(val, 1) << "bit 7 did not move to place 0";
	ASSERT_EQ(c.carry_flag, 1) << "carry flag did not update correctly";
}

TEST(Commands, RL_3) 
{
	cpu c = { 0 };
	byte val = 0b10101000;
	c.rl_n(&val, 3);
	ASSERT_EQ(val, 0b01000101);
	ASSERT_EQ(c.carry_flag, 1) << "carry flag did not update correctly";
}

TEST(Commands, RLC_1) 
{
	cpu c = { 0 };
	byte val = 1<<7;
	c.rlc_n(&val, 1);
	ASSERT_EQ(val, 0); 
	ASSERT_EQ(c.carry_flag, 1) << "carry flag did not update correctly";
}


TEST(Commands, RLC_3)
{
	cpu c = { 0 };
	byte val = 0b10101000;
	c.rlc_n(&val, 3);
	ASSERT_EQ(val, 0b01000010);
	ASSERT_EQ(c.carry_flag, 1) << "carry flag did not update correctly";
}



TEST(Commands, RR_1)
{
	cpu c = { 0 };
	byte val = 1;
	c.rr_n(&val, 1);
	ASSERT_EQ(val, 1<<7) << "bit 0 did not move to place 7";
	ASSERT_EQ(c.carry_flag, 1) << "carry flag did not update correctly";
}


TEST(Commands, RR_3)
{
	cpu c = { 0 };
	byte val = 0b01000101;
	c.rr_n(&val, 3);
	ASSERT_EQ(val, 0b10101000);
	ASSERT_EQ(c.carry_flag, 1);
}
