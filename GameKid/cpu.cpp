#include <GameKid/cpu.h>
#include <GameKid/opcodes.h>


void cpu::run()
{
	while (true)
	{
		next();
	}
}

void cpu::next()
{
	byte current_opcode = *code_mem;
	opcode_table[current_opcode]();
}

void cpu::initialize_misc()
{
	opcode_table[NOP] = [this]() {};
	opcode_table[CCF] = [this]() { ccf(); };
	opcode_table[SCF] = [this]() { scf(); };
	opcode_table[HALT] = [this]() { halt(); };
	
}

void cpu::initialize_opcode_table()
{
	opcode_table[CB_PREFIX] = [this]() { cb_prefix(); };

	initialize_misc();
	initialize_rotate_and_shifts();
	initialize_bit_opcodes();
}

void cpu::initialize_rotate_and_shifts()
{
	opcode_table[RLA] = [this](){ rla(); };
	opcode_table[RLCA] = [this](){ rlca(); };
	opcode_table[RRCA] = [this]() { rrca(); };
	opcode_table[RRA] = [this]() { rra(); };
	
	// RLC
	cb_prefix_table[CB_RLC_A] = [this]() { rlc(&A); };
	cb_prefix_table[CB_RLC_B] = [this]() { rlc(&B); };
	cb_prefix_table[CB_RLC_C] = [this]() { rlc(&C); };
	cb_prefix_table[CB_RLC_D] = [this]() { rlc(&D); };
	cb_prefix_table[CB_RLC_E] = [this]() { rlc(&E); };
	cb_prefix_table[CB_RLC_H] = [this]() { rlc(&H); };
	cb_prefix_table[CB_RLC_L] = [this]() { rlc(&L); };

	cb_prefix_table[CB_RL_A] = [this]() { rl(&A); };
	cb_prefix_table[CB_RL_B] = [this]() { rl(&B); };
	cb_prefix_table[CB_RL_C] = [this]() { rl(&C); };
	cb_prefix_table[CB_RL_D] = [this]() { rl(&D); };
	cb_prefix_table[CB_RL_E] = [this]() { rl(&E); };
	cb_prefix_table[CB_RL_H] = [this]() { rl(&H); };
	cb_prefix_table[CB_RL_L] = [this]() { rl(&L); };

	cb_prefix_table[CB_RR_A] = [this]() { rr(&A); };
	cb_prefix_table[CB_RR_B] = [this]() { rr(&B); };
	cb_prefix_table[CB_RR_C] = [this]() { rr(&C); };
	cb_prefix_table[CB_RR_D] = [this]() { rr(&D); };
	cb_prefix_table[CB_RR_E] = [this]() { rr(&E); };
	cb_prefix_table[CB_RR_H] = [this]() { rr(&H); };
	cb_prefix_table[CB_RR_L] = [this]() { rr(&L); };

	cb_prefix_table[CB_RRC_A] = [this]() { rrc(&A); };
	cb_prefix_table[CB_RRC_B] = [this]() { rrc(&B); };
	cb_prefix_table[CB_RRC_C] = [this]() { rrc(&C); };
	cb_prefix_table[CB_RRC_D] = [this]() { rrc(&D); };
	cb_prefix_table[CB_RRC_E] = [this]() { rrc(&E); };
	cb_prefix_table[CB_RRC_H] = [this]() { rrc(&H); };
	cb_prefix_table[CB_RRC_L] = [this]() { rrc(&L); };

	cb_prefix_table[CB_SLA_A] = [this]() { sla(&A); };
	cb_prefix_table[CB_SLA_B] = [this]() { sla(&B); };
	cb_prefix_table[CB_SLA_C] = [this]() { sla(&C); };
	cb_prefix_table[CB_SLA_D] = [this]() { sla(&D); };
	cb_prefix_table[CB_SLA_E] = [this]() { sla(&E); };
	cb_prefix_table[CB_SLA_H] = [this]() { sla(&H); };
	cb_prefix_table[CB_SLA_L] = [this]() { sla(&L); };

	cb_prefix_table[CB_SRA_A] = [this]() { sra(&A); };
	cb_prefix_table[CB_SRA_B] = [this]() { sra(&B); };
	cb_prefix_table[CB_SRA_C] = [this]() { sra(&C); };
	cb_prefix_table[CB_SRA_D] = [this]() { sra(&D); };
	cb_prefix_table[CB_SRA_E] = [this]() { sra(&E); };
	cb_prefix_table[CB_SRA_H] = [this]() { sra(&H); };
	cb_prefix_table[CB_SRA_L] = [this]() { sra(&L); };

	cb_prefix_table[CB_SRL_A] = [this]() { srl(&A); };
	cb_prefix_table[CB_SRL_B] = [this]() { srl(&B); };
	cb_prefix_table[CB_SRL_C] = [this]() { srl(&C); };
	cb_prefix_table[CB_SRL_D] = [this]() { srl(&D); };
	cb_prefix_table[CB_SRL_E] = [this]() { srl(&E); };
	cb_prefix_table[CB_SRL_H] = [this]() { srl(&H); };
	cb_prefix_table[CB_SRL_L] = [this]() { srl(&L); };
}

void cpu::initialize_bit_opcode(byte startOpcode, byte* address)
{
	for (int bitPlace = 0; bitPlace<8; ++bitPlace)
	{
		cb_prefix_table[startOpcode + bitPlace*8] = [this, address, bitPlace]()
		{
			bit(*address, bitPlace);
		};
	}
}

void cpu::initialize_bit_opcodes()
{
	initialize_bit_opcode(CB_BIT_b_A, &A);
	initialize_bit_opcode(CB_BIT_b_B, &B);
	initialize_bit_opcode(CB_BIT_b_C, &C);
	initialize_bit_opcode(CB_BIT_b_D, &D);
	initialize_bit_opcode(CB_BIT_b_E, &E);
	initialize_bit_opcode(CB_BIT_b_H, &H);
	initialize_bit_opcode(CB_BIT_b_L, &L);
}

void cpu::halt()
{
}

void cpu::stop()
{
}

void cpu::error()
{
}


void cpu::ccf()
{
	this->carry_flag ^= 1;
	this->half_carry_flag = 0;
	this->substruct_flag = 0;
}

void cpu::scf()
{
	this->half_carry_flag = 0;
	this->substruct_flag = 0;
	this->carry_flag = 1;
}

void cpu::rla()
{
	rl(&A);
}

void cpu::rlca()
{
	rlc(&A);
}

void cpu::rrca()
{
	rrc(&A);
}

void cpu::rra()
{
	rr(&A);
}

void cpu::bit(byte val, byte bitPlace)
{
	zero_flag = (val & (1 << bitPlace)) ? 0 : 1;
	substruct_flag = 0;
	half_carry_flag = 1;
}

void cpu::rl(byte* val)
{
	carry_flag = (*val & 128) ? 1 : 0;
	*val = (*val << 1) | carry_flag;
	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rlc(byte* val)
{
	byte old_carry = carry_flag;
	carry_flag = (*val & 128) ? 1 : 0;
	*val = (*val << 1) | old_carry;

	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rrc(byte* val)
{
	byte old_carry = carry_flag;
	carry_flag = (*val & 1) ? 1 : 0;
	*val = (*val >> 1) | (old_carry << 7);

	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rr(byte* val)
{
	carry_flag = (*val & 1) ? 1 : 0;
	*val = (*val >> 1) | (carry_flag << 7);

	// update flags
	this->half_carry_flag = 0;
	this->substruct_flag = 0;
	this->zero_flag = (*val == 0);
}

void cpu::sla(byte* val)
{
	carry_flag = (*val & 128) ? 1 : 0;
	*val <<= 1;
	zero_flag = (*val == 0);
	half_carry_flag = 0;
	substruct_flag = 0;

}

void cpu::sra(byte* val)
{
	carry_flag = *val & 1;
	*val = ((char)*val) >> 1;

	zero_flag = (*val == 0);
	half_carry_flag = 0;
	substruct_flag = 0;
}

void cpu::srl(byte* val)
{
	carry_flag = *val & 1;
	*val >>= 1;

	zero_flag = (*val == 0);
	half_carry_flag = 0;
	substruct_flag = 0;
}

void cpu::cb_prefix()
{
	code_mem++;
	byte second_opcode = *code_mem;
	cb_prefix_table[second_opcode]();
}
