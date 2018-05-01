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
	rl_n(&A, 1);
}

void cpu::rlca()
{
	rlc_n(&A, 1);
}

void cpu::rrca()
{
	rrc_n(&A, 1);
}

void cpu::rra()
{	
	rr_n(&A, 1);
}

void cpu::rl_n(byte* val, byte rotate)
{
	rotate %= 8;

	if (rotate != 0)
	{
		word w = *val;
		w <<= rotate;
		carry_flag = (w >> 8) & 1;
		*val = (w & 0xFF) | (w >> 8) & 0xFF;
	}
	
	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rlc_n(byte* val, byte rotate)
{
	rotate %= 8; // downgrade to 0-7

	if (rotate != 0)
	{
		word w = *val;
		w <<= 1;
		w |= carry_flag;
		w <<= (rotate - 1);
		carry_flag = (w >> 8) & 1;
		*val = (w & 0xFF) | (w >> 9) & 0xFF;
	}
	
	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rrc_n(byte* val, byte rotate)
{
	rotate %= 8; // downgrade to 0-7

	if (rotate != 0)
	{
		word w = *val;
		w <<= 1;
		w |= carry_flag;
		w <<= (8 - rotate);
		carry_flag = (w >> 8) & 1;
		*val = (w & 0xFF) | (w >> 9) & 0xFF;
	}

	zero_flag = (*val == 0);
	substruct_flag = 0;
	half_carry_flag = 0;
}

void cpu::rr_n(byte* val, const byte rotate)
{
	byte bitPlace = 1 << (rotate - 1);

	// set old bit 0 data
	this->carry_flag = *val & 1;
	
	// do rotation
	*val = (*val >> rotate) | (*val << (8 - rotate));

	// update flags
	this->half_carry_flag = 0;
	this->substruct_flag = 0;
	this->zero_flag = (*val == 0);
}

void cpu::sla_n(byte* val, byte shift)
{
	carry_flag = (*val >> (8 - shift)) & 1;
	*val <<= shift;
	zero_flag = (*val == 0);
	half_carry_flag = 0;
	substruct_flag = 0;
	
}

void cpu::sra_n(byte* val, byte shift)
{
	carry_flag = (*val >> (shift - 1)) & 1;
	*val >>= shift;
	zero_flag = (*val == 0);
	half_carry_flag = 0;
	substruct_flag = 0;
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
		break;
	case CB_SLA_n_B:
		sla_n(&B, *code_mem);
		break;
	case CB_SLA_n_C:
		sla_n(&C, *code_mem);
		break;
	case CB_SLA_n_D:
		sla_n(&D, *code_mem);
		break;
	case CB_SLA_n_E:
		sla_n(&E, *code_mem);
		break;
	case CB_SLA_n_H:
		sla_n(&H, *code_mem);
		break;
	case CB_SLA_n_HL:
		// use address space
		break;
	case CB_SRA_n_A:
		sra_n(&A, *code_mem);
		break;
	default:
		error();
		break;
	}
}
