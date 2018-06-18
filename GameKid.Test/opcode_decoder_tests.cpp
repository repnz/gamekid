#include "pch.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/opcode_decoder.h>


TEST(OPCODE_DECODER, DECODE)
{
    cpu c;
    instruction_set set(c);
    opcode_decoder d(set);
    
    for (const instruction* current_instruction : set.instructions())
    {
        for (opcode* current_opcode : *current_instruction)
        {
            opcode* decoded_opcode = d.decode(current_opcode->value.data());
            
            ASSERT_EQ(current_opcode, decoded_opcode)
                << "Opcode '" << current_opcode->name << "' does not decode correctly"
                << ". Decoded into " << ((decoded_opcode == nullptr) ? "nullptr" : decoded_opcode->name);
        }
    }
}