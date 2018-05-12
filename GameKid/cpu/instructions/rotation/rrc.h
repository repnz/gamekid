#pragma once

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

	void run(byte* val) override
	{
		_cpu.rrc(val);
	}
};
