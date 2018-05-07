#pragma once
#include <array>
#include <GameKid/cpu.h>
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/opcode.h>

class instruction
{
protected:
	cpu & _cpu;
public:

	std::string name;
	std::vector<opcode*> opcodes;

	instruction(cpu& cpu, const std::string& name) : _cpu(cpu), name(name) {}
	virtual ~instruction() = default;

};

class register_instruction : public instruction
{
public:
	register_instruction(cpu& cpu, std::string name, byte a, byte b, byte c,
		byte d, byte e, byte h, byte l) : instruction(cpu, name)
	{
		_operation = [this](byte* addr) {run_on_byte(addr); };

		add_register_opcode({ a }, "A", &cpu.A);
		add_register_opcode({ b }, "B", &cpu.B);
		add_register_opcode({ c }, "C", &cpu.C);
		add_register_opcode({ d }, "D", &cpu.D);
		add_register_opcode({ e }, "E", &cpu.E);
		add_register_opcode({ h }, "H", &cpu.H);
		add_register_opcode({ l }, "L", &cpu.L);
	}

	virtual void run_on_byte(byte* val) = 0;

private:
	std::vector<register_opcode> register_opcodes;
	std::function<void(byte*)> _operation;

	void add_register_opcode(
		const std::vector<byte>& bytes, 
		const std::string& register_name,
		byte* register_address
		)
	{
		register_opcodes.push_back(register_opcode(
			_cpu, 
			name, 
			bytes, 
			_operation, 
			register_name, 
			register_address
		));
	}

};
