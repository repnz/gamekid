#pragma once
#include "instruction.h"
#include <sstream>

class bit_operation_opcode : public opcode
{
private:
	byte _bit;
	std::function<void(byte*, byte)> _operation;
	byte* register_address;
	std::string register_name;
public:
	bit_operation_opcode(
		cpu& cpu,
		const std::string& name,
		byte base_value,
		const std::string& register_name,
		byte* register_address,
		bool cb_prefix,
		std::function<void(byte*, byte)> operation,
		byte bit)
		: opcode(cpu, name, base_value+bit*8, cb_prefix), 
	_bit(bit), _operation(operation), register_address(register_address),
	register_name(register_name)
	{
	}


	void run() override
	{
		_operation(register_address, _bit);
	}

	std::string to_str(byte* next) override
	{
		std::ostringstream ss;
		ss << name << " " << _bit << ", " << register_name;
		return ss.str();
	}
};

class bit_operation_instruction : instruction
{
public:
	bit_operation_instruction(cpu& cpu, const std::string& name, byte value, bool cb_prefix)
		: instruction(cpu, name), _value(value), _cb_prefix(cb_prefix)
	{
		_operation = [this](byte* address, byte bit) { this->run(address, bit); };
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		const int bit = atoi(operands[0].c_str());

		if (bit < 0 || bit > 7) { return {}; }

		const std::string& reg = operands[1];
		
		return _bit_opcodes[reg][bit].bytes();
	}

	virtual void run(byte* address, byte bit) = 0;
private:
	void add_register_opcodes(const std::string& register_name, byte* register_address)
	{
		for (byte bit = 0; bit<8; ++bit)
		{
			_bit_opcodes[register_name].push_back(
				bit_operation_opcode(
					_cpu,
					name,
					_value,
					register_name,
					register_address,
					_cb_prefix,
					_operation,
					bit
				)
			);
		}
	}

	std::function<void(byte*, byte)> _operation;
	bool _cb_prefix;
	byte _value;
	std::map<std::string, std::vector<bit_operation_opcode>> _bit_opcodes;

};

class bit_instruction : bit_operation_instruction
{
public:
	explicit bit_instruction(cpu& cpu)
		: bit_operation_instruction()
	{
	}

	void run(byte* val, byte bit) override
	{
	}
};
