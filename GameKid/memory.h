#pragma once
#include "cpu_types.h"

class memory
{
private:
	byte mem[64 * 1024];

public:
	void store(word address, byte value);
	byte load(word address);
};
