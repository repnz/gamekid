#include "pch.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/opcode_decoder.h>
#include <GameKid/utils/bytes.h>

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
            byte imm[4] = { 0 };

            if (current_opcode != decoded_opcode)
            {
                FAIL()
                    << "Opcode '" << current_opcode->to_str(imm) << "' does not decode correctly." << std::endl
                    << "Opcode byte: "
                    << std::hex << bytes::little_endian_decode<word>(current_opcode->value) << std::endl
                    << "Decoded into '"
                    << ((decoded_opcode == nullptr) ? "nullptr" : decoded_opcode->to_str(imm)) << "'";
            }   
        }
    }
}