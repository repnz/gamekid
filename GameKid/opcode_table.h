#pragma once
#include "cpu_types.h"
#include <map>
#include <functional>

class cpu;

class opcode_table
{
private:
	cpu* _cpu;
	void initialize_misc();
	void initialize_loads8();
	void initialize_opcode_table();
	void initialize_rotate_and_shifts();
	void initialize_bit_opcode(byte startOpcode, byte* address);
	void initialize_set_opcode(byte startOpcode, byte* address);
	void initialize_res_opcode(byte startOpcode, byte* address);
	void initialize_bit_opcodes();
	void initialize_alu8_opcodes();
	typedef std::function<void()> action;

	std::map<byte, action> _opcode_table;
	std::map<byte, action> _cb_prefix_table;
	void cb_prefix();

public:
	explicit opcode_table(cpu* c);
	void execute();
};