#include <GameKid/cpu.h>
#include <GameKid/opcodes.h>

cpu::cpu() : _opcode_table(this),
A(0), B(0), C(0), D(0), E(0), H(0), L(0), SP(0), PC(0),
zero_flag(0), substruct_flag(0), half_carry_flag(0), carry_flag(0)
{
}


void cpu::run()
{
	while (true)
	{
		next();
	}
}

void cpu::set(byte* val, byte bit_place)
{
	*val |= 1 << bit_place;
}

void cpu::res(byte* val, byte bit_place)
{
	*val &= ~(1 << bit_place);
}

void cpu::add(byte* val, byte n, bool carry)
{
	byte new_value = *val + n;
	
	if (carry)
	{
		new_value += carry_flag;
	}

	zero_flag = *val == 0;
	substruct_flag = 0;
	carry_flag = (new_value < *val) ? 1 : 0;
	half_carry_flag = ((new_value & 0xF) < (*val & 0xF)) ? 1 : 0;
	*val = new_value;
}

void cpu::adc(byte* val, byte n)
{
	add(val, n, true);
}

void cpu::sbc(byte* val, byte n)
{
	sub(val, n, true);
}

void cpu::and_n(byte* val, byte n)
{
	*val &= n;
	zero_flag = (*val == 0) ? 1 : 0;
	substruct_flag = 0;
	half_carry_flag = 1;
	carry_flag = 0;
}

void cpu::or_n(byte* val, byte n)
{
	*val |= n;
	zero_flag = (*val == 0) ? 1 : 0;
	half_carry_flag = 0;
	carry_flag = 0;
	substruct_flag = 0;
}

void cpu::xor_n(byte* a, byte byte)
{
	*a ^= byte;
	zero_flag = (*a == 0) ? 1 : 0;
	half_carry_flag = 0;
	carry_flag = 0;
	substruct_flag = 0;
}

void cpu::cp(byte val, byte byte)
{
	sub(&val, byte, false, false);
}

void cpu::set_zero_flag(byte val)
{
	zero_flag = (val == 0) ? 1 : 0;
}

void cpu::inc(byte* val)
{
	half_carry_flag = ((*val & 0xF) == 0b1111) ? 1 : 0;
	(*val)++;
	set_zero_flag(*val);
	substruct_flag = 0;
}

void cpu::dec(byte* val)
{
	half_carry_flag = ((*val >> 4) == 0b0001) ? 1 : 0;
	(*val)--;
	set_zero_flag(*val);
	substruct_flag = 1;
}

void cpu::swap(byte* val)
{
	*val = *val >> 4 | *val << 4;
	set_zero_flag(*val);
	half_carry_flag = 0;
	substruct_flag = 0;
	carry_flag = 0;
}

void cpu::sub(byte* val, byte n, bool carry, bool save_result)
{
	byte new_value = *val - n;

	if (carry)
	{
		new_value -= carry_flag;
	}

	zero_flag = new_value == 0 ? 1 : 0;
	substruct_flag = 1;
	carry_flag = (new_value > *val) ? 1 : 0;
	half_carry_flag = ((new_value & 0xF) > (*val & 0xF)) ? 1 : 0;

	if (save_result)
	{
		*val = new_value;
	}
}

void cpu::next()
{
	_opcode_table.execute();
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