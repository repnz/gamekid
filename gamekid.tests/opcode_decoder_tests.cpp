#include "pch.h"
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/opcode_decoder.h>
#include <gamekid/utils/bytes.h>
#include <gamekid/system.h>

namespace gamekid::tests {

    void decode_opcode_test(
        const cpu::opcode& opcode, 
        cpu::opcode_decoder& decoder
    );

    TEST(OPCODE_DECODER, DECODE) {
        system sys;
        cpu::cpu& cpu = sys.cpu();
        cpu::instruction_set set(cpu);
        cpu::opcode_decoder decoder(set);

        // Iterate and test all the opcodes
        for (const cpu::instruction* current_instruction : set.instructions()) {
            for (cpu::opcode* current_opcode : *current_instruction) {
                decode_opcode_test(*current_opcode, decoder);
            }
        }
    }

    void decode_opcode_test(const cpu::opcode& opcode, cpu::opcode_decoder& decoder) {
        const word opcode_word =
            gamekid::utils::bytes::little_endian_decode<word>(opcode.value);

        const cpu::opcode* decoded_opcode = decoder.decode(opcode_word);

        if (&opcode != decoded_opcode)
        {
            byte imm[4] = { 0 };

            FAIL()
                << "Opcode '" << opcode.to_str(imm) << "' does not decode correctly." << std::endl
                << "Opcode byte: "
                << std::hex << utils::bytes::little_endian_decode<word>(opcode.value) << std::endl
                << "Decoded into '"
                << ((decoded_opcode == nullptr) ? "nullptr" : decoded_opcode->to_str(imm)) << "'";
        }
    }
}