#include "pch.h"
#include <GameKid/cpu.h>


TEST(Commands, RL) 
{
	cpu c = { 0 };
	
	// 128 rl = 1
	byte val = 1<<7; 
	c.rl(&val);
	ASSERT_EQ(val, 1);
	ASSERT_EQ(c.carry_flag, 1);
	
	// 1 rl = 2
	val = 1;
	c.rl(&val);
	ASSERT_EQ(val, 2);
	ASSERT_EQ(c.carry_flag, 0);
}

TEST(Commands, RLC) 
{
	cpu c = { 0 };
	
	// 128 rlc (carry = 0) = 0
	byte val = 1<<7;
	c.rlc(&val);
	ASSERT_EQ(val, 0); 
	ASSERT_EQ(c.carry_flag, 1);

	// 1 rlc (carry = 1) = 3
	c.carry_flag = 1;
	val = 1;
	c.rlc(&val);
	ASSERT_EQ(val, 3);
	ASSERT_EQ(c.carry_flag, 0);
}


TEST(Commands, RR)
{
	cpu c = { 0 };
	
	// 1 rr == 128
	byte val = 1;
	c.rr(&val);
	ASSERT_EQ(val, 128);
	ASSERT_EQ(c.carry_flag, 1);

	// 128 rr == 64
	val = 128;
	c.carry_flag = 1;
	c.rr(&val);
	ASSERT_EQ(val, 64);
	ASSERT_EQ(c.carry_flag, 0);
}

TEST(Commands, RRC)
{
	cpu c = { 0 };

	// 1 rrc (carry = 0) == 0
	byte val = 1;
	c.rrc(&val);
	ASSERT_EQ(val, 0);
	ASSERT_EQ(c.carry_flag, 1);

	// 128 rrc (carry = 1) = 192
	c.carry_flag = 1;
	val = 128;
	c.rrc(&val);
	ASSERT_EQ(val, 192);
	ASSERT_EQ(c.carry_flag, 0);
}

TEST(Commands, SLA)
{
	cpu c = { 0 };
	
	// 128 sla == 0
	byte val = 0b10000000;
	c.sla(&val);
	ASSERT_EQ(val, 0);
	ASSERT_EQ(c.carry_flag, 1);

	// 64 sla == 128
	val = 0b01000000;
	c.sla(&val);
	ASSERT_EQ(val, 128);
	ASSERT_EQ(c.carry_flag, 0);
}

TEST(Commands, SRA)
{
	cpu c = { 0 };
	
	// 1 sra == 0
	byte val = 0b00000001;
	c.sra(&val);
	ASSERT_EQ(val, 0);
	ASSERT_EQ(c.carry_flag, 1);

	// -128 sra == -64
	val = 0b10000000; // -128
	c.sra(&val);
	ASSERT_EQ(val, 0b11000000); // -64
	ASSERT_EQ(c.carry_flag, 0);
}

TEST(Commands, SRL)
{
	cpu c = { 0 };

	// 1 srl == 0
	byte val = 0b00000001;
	c.sra(&val);
	ASSERT_EQ(val, 0);
	ASSERT_EQ(c.carry_flag, 1);

	// 128 srl == 64
	val = 0b10000000; 
	c.srl(&val);
	ASSERT_EQ(val, 0b01000000);
	ASSERT_EQ(c.carry_flag, 0);
}

TEST(Commands, BIT)
{
	cpu c = { 0 };

	// 1 bit 0 => zero_flag = 0
	byte val = 0b00000001;
	c.bit(val, 0);
	ASSERT_EQ(c.zero_flag, 0);

	// 1 bit 1 => zero_flag = 1
	val = 0b00000001;
	c.bit(val, 1);
	ASSERT_EQ(c.zero_flag, 1);
}

TEST(Commands, SET)
{
	cpu c = { 0 };

	// 0 set 3 => 0b00000100 => 4
	byte val = 0b00000000;
	c.set(&val, 2);
	ASSERT_EQ(val, 4);
}


TEST(Commands, RES)
{
	cpu c = { 0 };

	// 6 res 3 == 2
	byte val = 0b00000110;
	c.res(&val, 2);
	ASSERT_EQ(val, 2);
}

TEST(Commands, ADD)
{
	cpu c = { 0 };

	byte val = 10;
	c.add(&val, 2);
	ASSERT_EQ(val, 12);

	val = 255;
	c.add(&val, 1);
	ASSERT_EQ(val, 0);
	ASSERT_EQ(c.carry_flag, 1);

	val = 0b00001111;
	c.add(&val, 1);
	ASSERT_EQ(val, 16);
	ASSERT_EQ(c.half_carry_flag, 1);
}