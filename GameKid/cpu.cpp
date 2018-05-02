#include <GameKid/cpu.h>
#include <GameKid/opcodes.h>


void cpu::run()
{
	while (true)
	{
		switch (*code_mem)
		{
		case RLA:
			rla();
			break;
		case RLCA:
			rlca();
			break;
		case NOP:
			break;
		case CCF:
			ccf();
			break;
		case SCF:
			scf();
			break;
		case HALT:
			halt();
			break;
		case RRCA:
			rrca();
		case RRA:
			rra();
		case CB_PREFIX:
			cb_prefix();
		case 1:
			stop();
			break;
		default:
			error();
			break;
		}

		++code_mem;
	}
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
	byte second_opcode = *code_mem;
	code_mem++;
	switch (second_opcode)
	{
	case CB_RLC_A:
		rlc(&A);
		break;
	case CB_RLC_B:
		rlc(&B);
		break;
	case CB_RLC_C:
		rlc(&C);
		break;
	case CB_RLC_D:
		rlc(&D);
		break;
	case CB_RLC_E:
		rlc(&E);
		break;
	case CB_RLC_H:
		rlc(&H);
		break;
	case CB_RLC_L:
		rlc(&L);
		break;
	case CB_RLC_HL:
		// fix to memory
		//rlc_n<unsigned short>(nullptr, *code_mem, &carry_flag);
		break;
	case CB_RL_A:
		rl(&A);
		break;
	case CB_RL_B:
		rl(&B);
		break;
	case CB_RL_C:
		rl(&C);
		break;
	case CB_RL_D:
		rl(&D);
		break;
	case CB_RL_E:
		rl(&E);
		break;
	case CB_RL_H:
		rl(&H);
		break;
	case CB_RL_L:
		rl(&L);
		break;
	case CB_RL_HL:
		// use address space
		break;
	case CB_RRC_A:
		rrc(&A);
		break;
	case CB_SLA_B:
		sla(&B);
		break;
	case CB_SLA_C:
		sla(&C);
		break;
	case CB_SLA_D:
		sla(&D);
		break;
	case CB_SLA_E:
		sla(&E);
		break;
	case CB_SLA_H:
		sla(&H);
		break;
	case CB_SLA_HL:
		// use address space
		break;
	case CB_SRA_A:
		sra(&A);
		break;
	case CB_SRL_A:
		srl(&A);
	default:
		error();
		break;
	}
}
