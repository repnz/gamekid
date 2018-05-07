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
	std::vector<byte> bytes;
	
	opcode(cpu& cpu, const std::string& name, std::vector<byte> bytes)
		: _cpu(cpu), name(name), bytes(bytes)
	{
	}

	opcode& operator=(const opcode& op)
	{
		_cpu = op._cpu;
		name = op.name;
		bytes = op.bytes;
		return *this;
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
		const std::vector<byte>& bytes,
		const std::function<void(byte* addr)>& operation,
		const std::string& register_name,
		byte* register_address
	)
		: opcode(cpu, name, bytes),
		_operation(operation),
		register_name(register_name),
		register_address(register_address)
	{
	}
	
	register_opcode& operator=(const register_opcode& op)
	{
		opcode::operator=(op);
		register_name = op.register_name;
		register_address = op.register_address;
		return *this;
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

