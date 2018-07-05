#include "pch.h"
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/opcode_decoder.h>
#include <gamekid/utils/bytes.h>
#include <gamekid/system.h>

void decode_opcode_test(const gamekid::cpu::opcode& opcode, gamekid::cpu::opcode_decoder& decoder);

TEST(OPCODE_DECODER, DECODE)
{
    gamekid::system sys({});
    gamekid::cpu::cpu& cpu = sys.cpu();
    gamekid::cpu::instruction_set set(cpu);
    gamekid::cpu::opcode_decoder decoder(set);
    
    // Iterate and test all the opcodes
    for (const gamekid::cpu::instruction* current_instruction : set.instructions()) {
        for (gamekid::cpu::opcode* current_opcode : *current_instruction) {
            decode_opcode_test(*current_opcode, decoder);
        }
    }
}

void decode_opcode_test(const gamekid::cpu::opcode& opcode, gamekid::cpu::opcode_decoder& decoder) {
    const word opcode_word =
        gamekid::utils::bytes::little_endian_decode<word>(opcode.value);

    const gamekid::cpu::opcode* decoded_opcode = decoder.decode(opcode_word);

    byte imm[4] = { 0 };

    if (&opcode != decoded_opcode)
    {
        FAIL()
            << "Opcode '" << opcode.to_str(imm) << "' does not decode correctly." << std::endl
            << "Opcode byte: "
            << std::hex << gamekid::utils::bytes::little_endian_decode<word>(opcode.value) << std::endl
            << "Decoded into '"
            << ((decoded_opcode == nullptr) ? "nullptr" : decoded_opcode->to_str(imm)) << "'";
    }
}