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

void cpu::rla()
{
	rl_n(&A, 1);
}

void cpu::rlca()
{
	rlc_n(&A, 1);
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

void cpu::rrca()
{
	byte old_carry_flag = this->carry_flag;
	this->carry_flag = this->A & 1; // get bit 1
	this->A >>= 1;
	this->A += old_carry_flag<<7;
	this->substruct_flag = 0;
	this->half_carry_flag = 0;
	this->zero_flag = (this->A == 0);
}

void cpu::rra()
{	
	rr_n(&A, 1);
}

void cpu::rl_n(byte* val, const byte rotate)
{
	const byte bitPlace = 256 >> rotate;
	carry_flag = (*val &  bitPlace) ? 1 : 0;
	const byte right_side = (*val >> (8 - rotate) & (bitPlace - 1));
	const byte left_side = (*val << rotate);
	*val = right_side | left_side;
	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rlc_n(byte* val, const byte rotate)
{
	if (rotate != 0)
	{
		const byte right_side = 
			*val >> (8 - rotate + 1) &
			((256 >> rotate) - 2) |
			carry_flag;

		const byte left_side = (*val << rotate);
		carry_flag = (*val & (256 >> rotate)) ? 1 : 0;
		*val = right_side | left_side;
	}
	
	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rrc_n(byte* val, const byte rotate)
{
	byte bitPlace = 1 << rotate;
	byte old_carry_flag = this->carry_flag;
	this->carry_flag = *val & bitPlace;
	this->half_carry_flag = 0;
	this->substruct_flag = 0;
	*val = (*val >> rotate) | ((*val << 1)<< (rotate - 1));
	this->zero_flag = (*val == 0);
}

void cpu::rr_n(byte* val, const byte rotate)
{
	byte bitPlace = 1 << rotate;

	// update carry with old value
	this->carry_flag = *val & bitPlace;
	
	
	// do rotation
	*val = (*val >> rotate) | (*val << (rotate - 1));

	// update flags
	this->half_carry_flag = 0;
	this->substruct_flag = 0;
	this->zero_flag = (*val == 0);
}

void cpu::cb_prefix()
{
	byte second_opcode = *code_mem;
	code_mem++;
	switch (*code_mem)
	{
	case CB_RLC_n_A:
		rlc_n(&A, *code_mem);
		break;
	case CB_RLC_n_B:
		rlc_n(&B, *code_mem);
		break;
	case CB_RLC_n_C:
		rlc_n(&C, *code_mem);
		break;
	case CB_RLC_n_D:
		rlc_n(&D, *code_mem);
		break;
	case CB_RLC_n_E:
		rlc_n(&E, *code_mem);
		break;
	case CB_RLC_n_H:
		rlc_n(&H, *code_mem);
		break;
	case CB_RLC_n_L:
		rlc_n(&L, *code_mem);
		break;
	case CB_RLC_n_HL:
		// fix to memory
		//rlc_n<unsigned short>(nullptr, *code_mem, &carry_flag);
		break;
	case CB_RL_n_A:
		rl_n(&A, *code_mem);
		break;
	case CB_RL_n_B:
		rl_n(&B, *code_mem);
		break;
	case CB_RL_n_C:
		rl_n(&C, *code_mem);
		break;
	case CB_RL_n_D:
		rl_n(&D, *code_mem);
		break;
	case CB_RL_n_E:
		rl_n(&E, *code_mem);
		break;
	case CB_RL_n_H:
		rl_n(&H, *code_mem);
		break;
	case CB_RL_n_L:
		rl_n(&L, *code_mem);
		break;
	case CB_RL_n_HL:
		// use address space
		break;
	case CB_RRC_n_A:
		rrc_n(&A, *code_mem);
	default:
		error();
		break;
	}
}
