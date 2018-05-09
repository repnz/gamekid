#pragma once
#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu.h"
#include <vector>


class opcode
{
protected:
	cpu & _cpu;
public:
	std::string name;
	byte value;
	bool cb_prefix;
	
	opcode(cpu& cpu, const std::string& name, byte value, bool cb_prefix)
		: _cpu(cpu), name(name), value(value), cb_prefix(cb_prefix)
	{
	}

	virtual std::string to_str(byte* next) = 0;
	virtual void run() = 0;
	virtual ~opcode() = default;
};

class register_opcode : public opcode
{
private:
	std::function<void(byte* addr)> _operation;
public:
	std::string register_name;
	byte* register_address;

	
	register_opcode(
		cpu& cpu,
		const std::string& name,
		const byte value,
		const std::function<void(byte* addr)>& operation,
		const std::string& register_name,
		byte* register_address,
		bool cb_prefix
	)
		: opcode(cpu, name, value, cb_prefix),
		_operation(operation),
		register_name(register_name),
		register_address(register_address)
	{
	}
	
	void run() override
	{
		_operation(register_address);
	}

	std::string to_str(byte* next) override
	{
		return name + " " + register_name;
	}
};

