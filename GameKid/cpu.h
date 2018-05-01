#pragma once
#include <GameKid/types.h>

class cpu
{
public:
	byte A;
	byte B;
	byte C;
	byte D;
	byte E;
	byte H;
	byte L;
	word SP;
	word PC;

	byte zero_flag;
	byte substruct_flag;
	byte half_carry_flag;
	byte carry_flag;

	byte* memory;
	byte* code_mem;

	void halt();
	void stop();
	void error();
	void rla();
	void rlca();
	void ccf();
	void scf();
	void rrca();
	void rra();
	
	void rl_n(byte* val, byte rotate);
	void rlc_n(byte* val, byte rotate);
	void rrc_n(byte* val, byte code_mem);
	void rr_n(byte* val, byte code_mem);
	void cb_prefix();
	void run();
};