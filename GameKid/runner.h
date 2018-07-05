#include "system.h"
#include "cpu/cpu.h"
#include "cpu/instruction_set.h"
#include "cpu/opcode_decoder.h"
#include <set>

namespace gamekid {

    class runner
    {
    private:
        gamekid::system _system;
        gamekid::cpu::instruction_set _set;
        gamekid::cpu::opcode_decoder _decoder;
        std::set<word> _breakpoints;
    public:
        explicit runner(std::vector<byte>& rom);

        std::vector<std::string> list(int count);
        void add_breakpoint(word address);
        void run_until_break();
        void next();
        void run();
    };

}
