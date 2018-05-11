#pragma once
#include "instruction.h"
#include "GameKid/opcodes.h"

class rl_instruction : public register_instruction
{
public:
	explicit rl_instruction(cpu& cpu)
		: register_instruction(cpu, "rl", true,
			CB_RL_A,
			CB_RL_B,
			CB_RL_C,
			CB_RL_D,
			CB_RL_E,
			CB_RL_H,
			CB_RL_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.rl(val);
	}
};

class rla_opcode : public opcode
{
public:
	explicit rla_opcode(cpu& cpu)
		: opcode(cpu, "rla", RLA, false)
	{
	}

	void run() override
	{
		_cpu.rla();
	}
};

class rla_instruction : public instruction
{
private:
	rla_opcode _opcode;
public:
	explicit rla_instruction(cpu& cpu) : instruction(cpu, "rla"), _opcode(cpu)
	{
		opcodes.push_back(&_opcode);
	}


	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		if (operands.size() != 0) { return {}; }

		return { _opcode.value };
	}
};

class rr_instruction : public register_instruction
{
public:
	explicit rr_instruction(cpu& cpu)
		: register_instruction(cpu, "rr", true,
			CB_RR_A,
			CB_RR_B,
			CB_RR_C,
			CB_RR_D,
			CB_RR_E,
			CB_RR_H,
			CB_RR_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.rr(val);
	}
};

class rrc_instruction : public register_instruction
{
public:
	explicit rrc_instruction(cpu& cpu)
		: register_instruction(cpu, "rrc", true,
			CB_RRC_A,
			CB_RRC_B,
			CB_RRC_C,
			CB_RRC_D,
			CB_RRC_E,
			CB_RRC_H,
			CB_RRC_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.rrc(val);
	}
};

class rra_opcode : public opcode
{
public:
	explicit rra_opcode(cpu& cpu)
		: opcode(cpu, "rra", RRA, false)
	{
	}

	void run() override
	{
		_cpu.rla();
	}
};

class rra_instruction : public instruction
{
private:
	rra_opcode _opcode;
public:
	explicit rra_instruction(cpu& cpu) : instruction(cpu, "rra"), _opcode(cpu)
	{
		opcodes.push_back(&_opcode);
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		if (operands.size() != 0) { return {}; }

		return { _opcode.value };
	}
};

class rlc_instruction : public register_instruction
{
public:
	explicit rlc_instruction(cpu& cpu)
		: register_instruction(cpu, "rlc", true,
			CB_RLC_A,
			CB_RLC_B,
			CB_RLC_C,
			CB_RLC_D,
			CB_RLC_E,
			CB_RLC_H,
			CB_RLC_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.rlc(val);
	}
};

class rlca_opcode : public opcode
{
public:
	explicit rlca_opcode(cpu& cpu)
		: opcode(cpu, "rlca", RLCA, false)
	{
	}

	void run() override
	{
		_cpu.rlca();
	}
};

class rlca_instruction : public instruction
{
private:
	rra_opcode _opcode;
public:
	explicit rlca_instruction(cpu& cpu) : instruction(cpu, "rlca"), _opcode(cpu)
	{
		opcodes.push_back(&_opcode);
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		if (operands.size() != 0) { return {}; }

		return { _opcode.value };
	}

};

class rrca_opcode : public opcode
{
public:
	explicit rrca_opcode(cpu& cpu)
		: opcode(cpu, "rrca", RRCA, false)
	{
	}

	void run() override
	{
		_cpu.rrca();
	}
};

class rrca_instruction : public instruction
{
private:
	rra_opcode _opcode;
public:
	explicit rrca_instruction(cpu& cpu) : instruction(cpu, "rrca"), _opcode(cpu)
	{
		opcodes.push_back(&_opcode);
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		if (operands.size() != 0) { return {}; }

		return { _opcode.value };
	}

};

class sla_instruction : public register_instruction
{
public:
	explicit sla_instruction(cpu& cpu)
		: register_instruction(cpu, "sla", true,
			CB_SLA_A,
			CB_SLA_B,
			CB_SLA_C,
			CB_SLA_D,
			CB_SLA_E,
			CB_SLA_H,
			CB_SLA_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.sla(val);
	}
};

class sra_instruction : public register_instruction
{
public:
	explicit sra_instruction(cpu& cpu)
		: register_instruction(cpu, "sla", true,
			CB_SLA_A,
			CB_SLA_B,
			CB_SLA_C,
			CB_SLA_D,
			CB_SLA_E,
			CB_SLA_H,
			CB_SLA_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.sra(val);
	}
};

class srl_instruction : public register_instruction
{
public:
	explicit srl_instruction(cpu& cpu)
		: register_instruction(cpu, "srl", true,
			CB_SRL_A,
			CB_SRL_B,
			CB_SRL_C,
			CB_SRL_D,
			CB_SRL_E,
			CB_SRL_H,
			CB_SRL_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.srl(val);
	}
};