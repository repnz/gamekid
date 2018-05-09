#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/opcode.h>

class instruction
{
protected:
	cpu & _cpu;
	instruction(cpu& cpu, const std::string& name) : _cpu(cpu), name(name) {}
public:

	std::string name;
	std::vector<opcode*> opcodes;

	virtual ~instruction() = default;
	virtual std::vector<byte> parse(const std::vector<std::string>& operands) = 0;

};

class register_instruction : public instruction
{
private:
	std::map<std::string, register_opcode> _register_opcodes;
protected:
	register_instruction(cpu& cpu, std::string name, bool cb_prefix, byte a, byte b, byte c,
		byte d, byte e, byte h, byte l) : instruction(cpu, name)
	{
		_operation = [this](byte* addr) {run_on_byte(addr); };

		add_register_opcode(a, "A", &cpu.A, cb_prefix);
		add_register_opcode(b, "B", &cpu.B, cb_prefix);
		add_register_opcode(c, "C", &cpu.C, cb_prefix);
		add_register_opcode(d, "D", &cpu.D, cb_prefix);
		add_register_opcode(e, "E", &cpu.E, cb_prefix);
		add_register_opcode(h, "H", &cpu.H, cb_prefix);
		add_register_opcode(l, "L", &cpu.L, cb_prefix);
	}
public:
	

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		if (operands.size() != 1)
		{
			return {};
		}

		const std::string& register_name = operands[0];

		auto it = _register_opcodes.find(register_name);

		if (it == _register_opcodes.end())
		{
			return {};
		}

		return it->second.bytes();

	}

	virtual void run_on_byte(byte* val) = 0;

private:
	std::function<void(byte*)> _operation;

	void add_register_opcode(
		const byte value, 
		const std::string& register_name,
		byte* register_address,
		bool cb_prefix
		)
	{
		_register_opcodes.insert(make_pair(register_name, register_opcode(
			_cpu, 
			name, 
			value, 
			_operation, 
			register_name, 
			register_address,
			cb_prefix
		)));
			
		opcodes.push_back(&_register_opcodes.at(register_name));
	}
};
