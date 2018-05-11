#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/opcodes.h"

class sub_instruction : public register_instruction
{
public:
	explicit sub_instruction(cpu& cpu)
		: register_instruction(cpu, "sub", false,
			SUB_A_A, 
			SUB_A_B, 
			SUB_A_C,
			SUB_A_D,
			SUB_A_E, 
			SUB_A_H,
			SUB_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.sub(&_cpu.A, *val);
	}
};

class sbc_instruction : public register_instruction
{
public:
	explicit sbc_instruction(cpu& cpu)
		: register_instruction(cpu, "sbc", false,
			SBC_A_A,
			SBC_A_B,
			SBC_A_C,
			SBC_A_D,
			SBC_A_E,
			SBC_A_H,
			SBC_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.sub(&_cpu.A, *val, true);
	}
};


class add_instruction : public register_instruction
{
public:
	explicit add_instruction(cpu& cpu)
		: register_instruction(cpu, "add", false,
			ADD_A_A,
			ADD_A_B,
			ADD_A_C,
			ADD_A_D,
			ADD_A_E,
			ADD_A_H,
			ADD_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.add(&_cpu.A, *val);
	}
};


class adc_instruction : public register_instruction
{
public:
	explicit adc_instruction(cpu& cpu)
		: register_instruction(cpu, "adc", false,
			ADC_A_A,
			ADC_A_B,
			ADC_A_C,
			ADC_A_D,
			ADC_A_E,
			ADC_A_H,
			ADC_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.add(&_cpu.A, *val, true);
	}
};

class xor_instruction : public register_instruction
{
public:
	explicit xor_instruction(cpu& cpu)
		: register_instruction(cpu, "xor", false,
			XOR_A_A,
			XOR_A_B,
			XOR_A_C,
			XOR_A_D,
			XOR_A_E,
			XOR_A_H,
			XOR_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.xor_n(&_cpu.A, *val);
	}
};

class and_instruction : public register_instruction
{
public:
	explicit and_instruction(cpu& cpu)
		: register_instruction(cpu, "and", false,
			AND_A_A,
			AND_A_B,
			AND_A_C,
			AND_A_D,
			AND_A_E,
			AND_A_H,
			AND_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.and_n(&_cpu.A, *val);
	}
};

class or_instruction : public register_instruction
{
public:
	explicit or_instruction(cpu& cpu)
		: register_instruction(cpu, "and", false,
			AND_A_A,
			AND_A_B,
			AND_A_C,
			AND_A_D,
			AND_A_E,
			AND_A_H,
			AND_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.or_n(&_cpu.A, *val);
	}
};

class cp_instruction : public register_instruction
{
public:
	explicit cp_instruction(cpu& cpu)
		: register_instruction(cpu, "cp", false,
			CP_A_A,
			CP_A_B,
			CP_A_C,
			CP_A_D,
			CP_A_E,
			CP_A_H,
			CP_A_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.or_n(&_cpu.A, *val);
	}
};

class inc_instruction : public register_instruction
{
public:
	explicit inc_instruction(cpu& cpu)
		: register_instruction(cpu, "inc", false,
			INC_A,
			INC_B,
			INC_C,
			INC_D,
			INC_E,
			INC_H,
			INC_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.inc(val);
	}
};

class dec_instruction : public register_instruction
{
public:
	explicit dec_instruction(cpu& cpu)
		: register_instruction(cpu, "dec", false,
			DEC_A,
			DEC_B,
			DEC_C,
			DEC_D,
			DEC_E,
			DEC_H,
			DEC_L)
	{
	}

	void run_on_byte(byte* val) override
	{
		_cpu.inc(val);
	}
};