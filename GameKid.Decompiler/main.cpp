#include <GameKid/cpu/opcode_decoder.h>

int main()
{    
    cpu cpu;
    instruction_set s(cpu);
    opcode_decoder d(s);
}