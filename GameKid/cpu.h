#pragma once
#include <GameKid/cpu_types.h>
#include <GameKid/opcode_table.h>

class cpu
{	
private:
	opcode_table _opcode_table;
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
	
	cpu();

	void next();
	
	void halt();
	void stop();
	void error();
	void rla();
	void rlca();
	void ccf();
	void scf();
	void rrca();
	void rra();
	void bit(byte val, byte bitPlace);
	void rl(byte* val);
	void rlc(byte* val);
	void rrc(byte* val);
	void rr(byte* val);
	void sla(byte* val);
	void sra(byte* val);
	void srl(byte* val);
	void run();
	void set(byte* val, byte bit_place);
	void res(byte* val, byte bit_place);
	void add(byte* val, byte n, bool carry = false);
	void adc(byte* val, byte n);
	void sub(byte* val, byte n, bool carry = false, bool save_result = true);
	void sbc(byte* val, byte n);
	void and_n(byte* val, byte n);
	void or_n(byte* val, byte n);
	void xor_n(byte* a, byte byte);
	void cp(byte val, byte byte);
	void set_zero_flag(byte val);
	void inc(byte* val);
	void dec(byte* val);
	void swap(byte* val);
};
