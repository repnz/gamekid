#include "cpu.h"
#include "cpu/instruction_set.h"
#include "cpu/opcode_decoder.h"
#include <set>

class runner
{
private:
    cpu _cpu;
    instruction_set _set;
    opcode_decoder _decoder;
    std::vector<byte> _rom;
    std::set<word> _breakpoints;
public:
    explicit runner(std::vector<byte>&& rom);

    std::vector<std::string> list(int count);
    void add_breakpoint(word address);
    void run_until_break();
    void next();
    void run();

    memory& memory() { return _cpu.mem; }
    cpu& cpu() { return _cpu; }
};
