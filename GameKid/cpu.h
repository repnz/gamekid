#pragma once
#include <GameKid/cpu_types.h>
#include <map>
#include <functional>

class cpu
{
private:
	void initialize_misc();
	void initialize_opcode_table();
	void initialize_rotate_and_shifts();
	void initialize_bit_opcode(byte startOpcode, byte* address);
	void initialize_set_opcode(byte startOpcode, byte* address);
	void initialize_res_opcode(byte startOpcode, byte* address);
	void initialize_bit_opcodes();
	void initialize_alu8_opcodes();
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

	typedef std::function<void()> action;

	std::map<byte, action> opcode_table;
	std::map<byte, action> cb_prefix_table;
		
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
	void cb_prefix();
	void run();
	void set(byte* val, byte bit_place);
	void res(byte* val, byte bit_place);
	void add(byte* val, byte n, bool carry = false);
	void adc(byte* val, byte n);
	void sub(byte* val, byte n, bool carry = false);
	void sbc(byte* val, byte n);
	void and_n(byte* val, byte n);
};
