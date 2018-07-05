#pragma once
#include <gamekid/cpu/instruction_set.h>
#include <map>

namespace gamekid::cpu {
    class opcode_decoder {
    private:
        std::map<word, opcode*> _opcode_table;
        instruction_set & _set;
        void initialize_tables();
    public:
        explicit opcode_decoder(instruction_set& set);
        opcode* decode(word opcode_bytes);
    };

}