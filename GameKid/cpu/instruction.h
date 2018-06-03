#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/opcode.h>
#include <memory>

class instruction
{
private:
    std::vector<std::unique_ptr<opcode>> _opcodes;
    std::vector<opcode*> _opcodes_ptr;
public:
    cpu & _cpu;
    instruction(cpu& cpu, const std::string& name) : _cpu(cpu), name(name) {}

    void add_opcode(std::unique_ptr<opcode> opcode)
    {
        _opcodes_ptr.push_back(opcode.get());
        _opcodes.push_back(std::move(opcode));
    }

    virtual ~instruction() = default;

    std::string name;
    const std::vector<opcode*>& opcodes()
    {
        return _opcodes_ptr;
    }

    virtual std::vector<byte> parse(const std::vector<std::string>& operands)
    {
        // leave parsing for later
        return {};
    }
};

