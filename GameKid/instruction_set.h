#pragma once
#include <vector>
#include "cpu_types.h"
#include <string>
#include "cpu.h"
#include <array>

class instruction_set;

class instruction_opcode
{
public:
	virtual ~instruction_opcode() = default;
	std::vector<byte> opcode;
	std::string name;
	
	virtual std::string to_str(byte* next) = 0;
	virtual void run(cpu* cpu) = 0;
};

class register_opcode : public instruction_opcode
{
public:
	std::string register_name;
	byte* register_address;

	virtual void run(cpu* cpu, byte* register_value) = 0;

	void run(cpu* cpu) override
	{
		run(cpu, register_address);
	}

	std::string to_str(byte* next) override
	{
		return name + " " + register_name;
	}
	
};

class instruction
{
public:
	std::vector<instruction_opcode*> opcodes;
	std::string name;
};

class register_instruction : public instruction
{
private:
	std::array<register_opcode, 7> _arr;
public:
	register_instruction(byte a, byte b, byte c,
		byte d, byte e, byte h, byte l)
	{
	}
};

class instruction_set
{
	std::vector<instruction> instructions;

	instruction_set();
};