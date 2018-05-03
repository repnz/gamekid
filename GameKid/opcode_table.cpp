#include "opcode_table.h"
#include <GameKid/opcodes.h>
#include <GameKid/cpu.h>

void opcode_table::initialize_misc()
{
	_opcode_table[NOP] = [this]() {};
	_opcode_table[CCF] = [this]() { _cpu->ccf(); };
	_opcode_table[SCF] = [this]() { _cpu->scf(); };
	_opcode_table[HALT] = [this]() { _cpu->halt(); };

	_cb_prefix_table[CB_SWAP_A] = [this]() {_cpu->swap(&_cpu->A); };
	_cb_prefix_table[CB_SWAP_B] = [this]() {_cpu->swap(&_cpu->B); };
	_cb_prefix_table[CB_SWAP_C] = [this]() {_cpu->swap(&_cpu->C); };
	_cb_prefix_table[CB_SWAP_D] = [this]() {_cpu->swap(&_cpu->D); };
	_cb_prefix_table[CB_SWAP_E] = [this]() {_cpu->swap(&_cpu->E); };
	_cb_prefix_table[CB_SWAP_H] = [this]() {_cpu->swap(&_cpu->H); };
	_cb_prefix_table[CB_SWAP_L] = [this]() {_cpu->swap(&_cpu->L); };
}

void opcode_table::initialize_opcode_table()
{
	_opcode_table[CB_PREFIX] = [this]() { this->cb_prefix(); };

	initialize_alu8_opcodes();
	initialize_misc();
	initialize_rotate_and_shifts();
	initialize_bit_opcodes();

}

void opcode_table::initialize_rotate_and_shifts()
{
	_opcode_table[RLA] = [this]() { _cpu->rla(); };
	_opcode_table[RLCA] = [this]() {_cpu->rlca(); };
	_opcode_table[RRCA] = [this]() { _cpu->rrca(); };
	_opcode_table[RRA] = [this]() { _cpu->rra(); };

	// RLC
	_cb_prefix_table[CB_RLC_A] = [this]() { _cpu->rlc(&_cpu->A); };
	_cb_prefix_table[CB_RLC_B] = [this]() { _cpu->rlc(&_cpu->B); };
	_cb_prefix_table[CB_RLC_C] = [this]() { _cpu->rlc(&_cpu->C); };
	_cb_prefix_table[CB_RLC_D] = [this]() { _cpu->rlc(&_cpu->D); };
	_cb_prefix_table[CB_RLC_E] = [this]() { _cpu->rlc(&_cpu->E); };
	_cb_prefix_table[CB_RLC_H] = [this]() { _cpu->rlc(&_cpu->H); };
	_cb_prefix_table[CB_RLC_L] = [this]() { _cpu->rlc(&_cpu->L); };

	_cb_prefix_table[CB_RL_A] = [this]() { _cpu->rl(&_cpu->A); };
	_cb_prefix_table[CB_RL_B] = [this]() { _cpu->rl(&_cpu->B); };
	_cb_prefix_table[CB_RL_C] = [this]() { _cpu->rl(&_cpu->C); };
	_cb_prefix_table[CB_RL_D] = [this]() { _cpu->rl(&_cpu->D); };
	_cb_prefix_table[CB_RL_E] = [this]() { _cpu->rl(&_cpu->E); };
	_cb_prefix_table[CB_RL_H] = [this]() { _cpu->rl(&_cpu->H); };
	_cb_prefix_table[CB_RL_L] = [this]() { _cpu->rl(&_cpu->L); };

	_cb_prefix_table[CB_RR_A] = [this]() { _cpu->rr(&_cpu->A); };
	_cb_prefix_table[CB_RR_B] = [this]() { _cpu->rr(&_cpu->B); };
	_cb_prefix_table[CB_RR_C] = [this]() { _cpu->rr(&_cpu->C); };
	_cb_prefix_table[CB_RR_D] = [this]() { _cpu->rr(&_cpu->D); };
	_cb_prefix_table[CB_RR_E] = [this]() { _cpu->rr(&_cpu->E); };
	_cb_prefix_table[CB_RR_H] = [this]() { _cpu->rr(&_cpu->H); };
	_cb_prefix_table[CB_RR_L] = [this]() { _cpu->rr(&_cpu->L); };

	_cb_prefix_table[CB_RRC_A] = [this]() { _cpu->rrc(&_cpu->A); };
	_cb_prefix_table[CB_RRC_B] = [this]() { _cpu->rrc(&_cpu->B); };
	_cb_prefix_table[CB_RRC_C] = [this]() { _cpu->rrc(&_cpu->C); };
	_cb_prefix_table[CB_RRC_D] = [this]() {_cpu->rrc(&_cpu->D); };
	_cb_prefix_table[CB_RRC_E] = [this]() { _cpu->rrc(&_cpu->E); };
	_cb_prefix_table[CB_RRC_H] = [this]() { _cpu->rrc(&_cpu->H); };
	_cb_prefix_table[CB_RRC_L] = [this]() { _cpu->rrc(&_cpu->L); };

	_cb_prefix_table[CB_SLA_A] = [this]() { _cpu->sla(&_cpu->A); };
	_cb_prefix_table[CB_SLA_B] = [this]() { _cpu->sla(&_cpu->B); };
	_cb_prefix_table[CB_SLA_C] = [this]() { _cpu->sla(&_cpu->C); };
	_cb_prefix_table[CB_SLA_D] = [this]() { _cpu->sla(&_cpu->D); };
	_cb_prefix_table[CB_SLA_E] = [this]() { _cpu->sla(&_cpu->E); };
	_cb_prefix_table[CB_SLA_H] = [this]() { _cpu->sla(&_cpu->H); };
	_cb_prefix_table[CB_SLA_L] = [this]() { _cpu->sla(&_cpu->L); };

	_cb_prefix_table[CB_SRA_A] = [this]() { _cpu->sra(&_cpu->A); };
	_cb_prefix_table[CB_SRA_B] = [this]() { _cpu->sra(&_cpu->B); };
	_cb_prefix_table[CB_SRA_C] = [this]() { _cpu->sra(&_cpu->C); };
	_cb_prefix_table[CB_SRA_D] = [this]() { _cpu->sra(&_cpu->D); };
	_cb_prefix_table[CB_SRA_E] = [this]() { _cpu->sra(&_cpu->E); };
	_cb_prefix_table[CB_SRA_H] = [this]() { _cpu->sra(&_cpu->H); };
	_cb_prefix_table[CB_SRA_L] = [this]() { _cpu->sra(&_cpu->L); };

	_cb_prefix_table[CB_SRL_A] = [this]() { _cpu->srl(&_cpu->A); };
	_cb_prefix_table[CB_SRL_B] = [this]() { _cpu->srl(&_cpu->B); };
	_cb_prefix_table[CB_SRL_C] = [this]() { _cpu->srl(&_cpu->C); };
	_cb_prefix_table[CB_SRL_D] = [this]() { _cpu->srl(&_cpu->D); };
	_cb_prefix_table[CB_SRL_E] = [this]() { _cpu->srl(&_cpu->E); };
	_cb_prefix_table[CB_SRL_H] = [this]() { _cpu->srl(&_cpu->H); };
	_cb_prefix_table[CB_SRL_L] = [this]() { _cpu->srl(&_cpu->L); };
}

void opcode_table::initialize_bit_opcode(byte startOpcode, byte* address)
{
	for (int bitPlace = 0; bitPlace<8; ++bitPlace)
	{
		_cb_prefix_table[startOpcode + bitPlace * 8] = [this, address, bitPlace]()
		{
			_cpu->bit(*address, bitPlace);
		};
	}
}

void opcode_table::initialize_set_opcode(byte startOpcode, byte* address)
{
	for (int bitPlace = 0; bitPlace<8; ++bitPlace)
	{
		_cb_prefix_table[startOpcode + bitPlace * 8] = [this, address, bitPlace]()
		{
			_cpu->set(address, bitPlace);
		};
	}
}

void opcode_table::initialize_res_opcode(byte startOpcode, byte* address)
{
	for (int bitPlace = 0; bitPlace<8; ++bitPlace)
	{
		_cb_prefix_table[startOpcode + bitPlace * 8] = [this, address, bitPlace]()
		{
			_cpu->res(address, bitPlace);
		};
	}
}

void opcode_table::initialize_bit_opcodes()
{
	initialize_bit_opcode(CB_BIT_b_A, &_cpu->A);
	initialize_bit_opcode(CB_BIT_b_B, &_cpu->B);
	initialize_bit_opcode(CB_BIT_b_C, &_cpu->C);
	initialize_bit_opcode(CB_BIT_b_D, &_cpu->D);
	initialize_bit_opcode(CB_BIT_b_E, &_cpu->E);
	initialize_bit_opcode(CB_BIT_b_H, &_cpu->H);
	initialize_bit_opcode(CB_BIT_b_L, &_cpu->L);

	initialize_bit_opcode(CB_SET_b_A, &_cpu->A);
	initialize_bit_opcode(CB_SET_b_B, &_cpu->B);
	initialize_bit_opcode(CB_SET_b_C, &_cpu->C);
	initialize_bit_opcode(CB_SET_b_D, &_cpu->D);
	initialize_bit_opcode(CB_SET_b_E, &_cpu->E);
	initialize_bit_opcode(CB_SET_b_H, &_cpu->H);
	initialize_bit_opcode(CB_SET_b_L, &_cpu->L);

	initialize_res_opcode(CB_RES_b_A, &_cpu->A);
	initialize_res_opcode(CB_RES_b_B, &_cpu->B);
	initialize_res_opcode(CB_RES_b_C, &_cpu->C);
	initialize_res_opcode(CB_RES_b_D, &_cpu->D);
	initialize_res_opcode(CB_RES_b_E, &_cpu->E);
	initialize_res_opcode(CB_RES_b_H, &_cpu->H);
	initialize_res_opcode(CB_RES_b_L, &_cpu->L);
}

void opcode_table::initialize_alu8_opcodes()
{
	_opcode_table[ADD_A_A] = [this]() { _cpu->add(&_cpu->A, _cpu->A); };
	_opcode_table[ADD_A_B] = [this]() { _cpu->add(&_cpu->A, _cpu->B); };
	_opcode_table[ADD_A_C] = [this]() { _cpu->add(&_cpu->A, _cpu->C); };
	_opcode_table[ADD_A_D] = [this]() { _cpu->add(&_cpu->A, _cpu->D); };
	_opcode_table[ADD_A_E] = [this]() { _cpu->add(&_cpu->A, _cpu->E); };
	_opcode_table[ADD_A_H] = [this]() { _cpu->add(&_cpu->A, _cpu->H); };
	_opcode_table[ADD_A_L] = [this]() { _cpu->add(&_cpu->A, _cpu->L); };
	_opcode_table[ADD_A_IMM] = [this]()
	{
		_cpu->add(&_cpu->A, _cpu->mem.load(_cpu->PC+1));
		_cpu->PC += 2;
	};

	_opcode_table[ADC_A_A] = [this]() { _cpu->adc(&_cpu->A, _cpu->A); };
	_opcode_table[ADC_A_B] = [this]() { _cpu->adc(&_cpu->A, _cpu->B); };
	_opcode_table[ADC_A_C] = [this]() { _cpu->adc(&_cpu->A, _cpu->C); };
	_opcode_table[ADC_A_D] = [this]() { _cpu->adc(&_cpu->A, _cpu->D); };
	_opcode_table[ADC_A_E] = [this]() { _cpu->adc(&_cpu->A, _cpu->E); };
	_opcode_table[ADC_A_H] = [this]() { _cpu->adc(&_cpu->A, _cpu->H); };
	_opcode_table[ADC_A_L] = [this]() { _cpu->adc(&_cpu->A, _cpu->L); };
	_opcode_table[ADC_A_IMM] = [this]()
	{
		_cpu->adc(&_cpu->A, _cpu->mem.load(_cpu->PC + 1));
		_cpu->PC += 2;
	};

	_opcode_table[SUB_A_A] = [this]() { _cpu->sub(&_cpu->A, _cpu->A); };
	_opcode_table[SUB_A_B] = [this]() { _cpu->sub(&_cpu->A, _cpu->B); };
	_opcode_table[SUB_A_C] = [this]() { _cpu->sub(&_cpu->A, _cpu->C); };
	_opcode_table[SUB_A_D] = [this]() { _cpu->sub(&_cpu->A, _cpu->D); };
	_opcode_table[SUB_A_E] = [this]() { _cpu->sub(&_cpu->A, _cpu->E); };
	_opcode_table[SUB_A_H] = [this]() { _cpu->sub(&_cpu->A, _cpu->H); };
	_opcode_table[SUB_A_L] = [this]() { _cpu->sub(&_cpu->A, _cpu->L); };
	_opcode_table[SUB_A_IMM] = [this]()
	{
		_cpu->sub(&_cpu->A, _cpu->mem.load(_cpu->PC + 1));
		_cpu->PC += 2;
	};

	_opcode_table[SBC_A_A] = [this]() { _cpu->sbc(&_cpu->A, _cpu->A); };
	_opcode_table[SBC_A_B] = [this]() { _cpu->sbc(&_cpu->A, _cpu->B); };
	_opcode_table[SBC_A_C] = [this]() { _cpu->sbc(&_cpu->A, _cpu->C); };
	_opcode_table[SBC_A_D] = [this]() { _cpu->sbc(&_cpu->A, _cpu->D); };
	_opcode_table[SBC_A_E] = [this]() { _cpu->sbc(&_cpu->A, _cpu->E); };
	_opcode_table[SBC_A_H] = [this]() { _cpu->sbc(&_cpu->A, _cpu->H); };
	_opcode_table[SBC_A_L] = [this]() { _cpu->sbc(&_cpu->A, _cpu->L); };
	_opcode_table[SBC_A_IMM] = [this]()
	{
		_cpu->sbc(&_cpu->A, _cpu->mem.load(_cpu->PC + 1));
		_cpu->PC += 2;
	};

	_opcode_table[AND_A_A] = [this]() { _cpu->and_n(&_cpu->A, _cpu->A); };
	_opcode_table[AND_A_B] = [this]() { _cpu->and_n(&_cpu->A, _cpu->B); };
	_opcode_table[AND_A_C] = [this]() { _cpu->and_n(&_cpu->A, _cpu->C); };
	_opcode_table[AND_A_D] = [this]() { _cpu->and_n(&_cpu->A, _cpu->D); };
	_opcode_table[AND_A_E] = [this]() { _cpu->and_n(&_cpu->A, _cpu->E); };
	_opcode_table[AND_A_H] = [this]() { _cpu->and_n(&_cpu->A, _cpu->H); };
	_opcode_table[AND_A_L] = [this]() { _cpu->and_n(&_cpu->A, _cpu->L); };
	_opcode_table[AND_A_IMM] = [this]()
	{
		_cpu->and_n(&_cpu->A, _cpu->mem.load(_cpu->PC+1));
		_cpu->PC += 2;
	};

	_opcode_table[OR_A_A] = [this]() { _cpu->or_n(&_cpu->A, _cpu->A); };
	_opcode_table[OR_A_B] = [this]() { _cpu->or_n(&_cpu->A, _cpu->B); };
	_opcode_table[OR_A_C] = [this]() { _cpu->or_n(&_cpu->A, _cpu->C); };
	_opcode_table[OR_A_D] = [this]() { _cpu->or_n(&_cpu->A, _cpu->D); };
	_opcode_table[OR_A_E] = [this]() { _cpu->or_n(&_cpu->A, _cpu->E); };
	_opcode_table[OR_A_H] = [this]() { _cpu->or_n(&_cpu->A, _cpu->H); };
	_opcode_table[OR_A_L] = [this]() { _cpu->or_n(&_cpu->A, _cpu->L); };
	_opcode_table[OR_A_IMM] = [this]()
	{
		_cpu->or_n(&_cpu->A, _cpu->mem.load(_cpu->PC+1));
		_cpu->PC += 2;
	};

	_opcode_table[XOR_A_A] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->A); };
	_opcode_table[XOR_A_B] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->B); };
	_opcode_table[XOR_A_C] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->C); };
	_opcode_table[XOR_A_D] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->D); };
	_opcode_table[XOR_A_E] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->E); };
	_opcode_table[XOR_A_H] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->H); };
	_opcode_table[XOR_A_L] = [this]() { _cpu->xor_n(&_cpu->A, _cpu->L); };
	_opcode_table[XOR_A_IMM] = [this]()
	{
		_cpu->xor_n(&_cpu->A, _cpu->mem.load(_cpu->PC+1));
		_cpu->PC += 2;
	};

	_opcode_table[CP_A_A] = [this]() { _cpu->cp(_cpu->A, _cpu->A); };
	_opcode_table[CP_A_B] = [this]() { _cpu->cp(_cpu->A, _cpu->B); };
	_opcode_table[CP_A_C] = [this]() { _cpu->cp(_cpu->A, _cpu->C); };
	_opcode_table[CP_A_D] = [this]() { _cpu->cp(_cpu->A, _cpu->D); };
	_opcode_table[CP_A_E] = [this]() { _cpu->cp(_cpu->A, _cpu->E); };
	_opcode_table[CP_A_H] = [this]() { _cpu->cp(_cpu->A, _cpu->H); };
	_opcode_table[CP_A_L] = [this]() { _cpu->cp(_cpu->A, _cpu->L); };
	_opcode_table[CP_A_IMM] = [this]()
	{
		_cpu->cp(_cpu->A, _cpu->mem.load(_cpu->PC+1));
		_cpu->PC += 2;
	};

	_opcode_table[INC_A] = [this]() { _cpu->inc(&_cpu->A); };
	_opcode_table[INC_B] = [this]() { _cpu->inc(&_cpu->B); };
	_opcode_table[INC_C] = [this]() { _cpu->inc(&_cpu->C); };
	_opcode_table[INC_D] = [this]() { _cpu->inc(&_cpu->D); };
	_opcode_table[INC_E] = [this]() { _cpu->inc(&_cpu->E); };
	_opcode_table[INC_H] = [this]() { _cpu->inc(&_cpu->H); };
	_opcode_table[INC_L] = [this]() { _cpu->inc(&_cpu->L); };

	_opcode_table[DEC_A] = [this]() { _cpu->dec(&_cpu->A); };
	_opcode_table[DEC_B] = [this]() { _cpu->dec(&_cpu->B); };
	_opcode_table[DEC_C] = [this]() { _cpu->dec(&_cpu->C); };
	_opcode_table[DEC_D] = [this]() { _cpu->dec(&_cpu->D); };
	_opcode_table[DEC_E] = [this]() { _cpu->dec(&_cpu->E); };
	_opcode_table[DEC_H] = [this]() { _cpu->dec(&_cpu->H); };
	_opcode_table[DEC_L] = [this]() { _cpu->dec(&_cpu->L); };
}

void opcode_table::cb_prefix()
{
	_cb_prefix_table[_cpu->mem.load(_cpu->PC+1)]();
}

opcode_table::opcode_table(cpu* c) : _cpu(c)
{
}

void opcode_table::execute()
{
	_opcode_table[_cpu->mem.load(_cpu->PC)]();
}
