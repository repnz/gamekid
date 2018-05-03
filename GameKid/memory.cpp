#include "memory.h"

void memory::store(word address, byte value)
{
	mem[address] = value;
}

byte memory::load(word address)
{
	return mem[address];
}
