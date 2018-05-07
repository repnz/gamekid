#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu.h"
#include <vector>

class opcode
{
public:
	virtual ~opcode() = default;
	std::string name;
	std::vector<byte> bytes;

	opcode(const std::string& name, std::vector<byte> bytes)
		: name(name), bytes(bytes)
	{
	}

	virtual std::string to_str(byte* next) = 0;
	virtual void run(cpu* cpu) = 0;
};

class register_opcode : public opcode
{
private:
	std::function<void(cpu* cpu, byte* addr)> _operation;
public:
	std::string register_name;
	byte* register_address;


	register_opcode(
		const std::string& name,
		const std::vector<byte>& opcode,
		const std::function<void(cpu* cpu, byte* addr)>& operation,
		const std::string& register_name,
		byte* register_address
	)
		: opcode(name, opcode),
		_operation(operation),
		register_name(register_name),
		register_address(register_address)
	{
	}

	void run(cpu* cpu) override
	{
		_operation(cpu, register_address);
	}

	std::string to_str(byte* next) override
	{
		return name + " " + register_name;
	}
};

