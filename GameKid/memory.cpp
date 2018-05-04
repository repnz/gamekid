#include "memory.h"

void memory::store(word address, byte value)
{
	mem[address] = value;
}

byte memory::load_byte(word address)
{
	return mem[address];
}

word memory::load_word_le(word address)
{
	return *(word*)mem[address];
}
