#pragma once
#include <gamekid/cpu/cpu.h>
#include <gamekid/utils/types.h>
#include <gamekid/cpu/opcode.h>
#include <memory>

namespace gamekid::cpu {
    class instruction {
    private:
        std::vector<std::unique_ptr<opcode>> _opcodes;
        std::vector<opcode*> _opcodes_ptr;
    public:
        cpu & _cpu;
        const std::string name;

        instruction(cpu& cpu, const std::string& name) : _cpu(cpu), name(name) {
            if (name.size() == 0) {
                throw "Instruction Name Is Empty";
            }
        }

        void add_opcode(std::unique_ptr<opcode> opcode) {
            _opcodes_ptr.push_back(opcode.get());
            _opcodes.push_back(std::move(opcode));
        }

        virtual ~instruction() = default;

        std::vector<opcode*>::iterator begin() { return _opcodes_ptr.begin(); }
        std::vector<opcode*>::iterator end() { return _opcodes_ptr.end(); }
        std::vector<opcode*>::const_iterator begin() const { return _opcodes_ptr.cbegin(); }
        std::vector<opcode*>::const_iterator end() const { return _opcodes_ptr.cend(); }

        virtual std::vector<byte> encode(const std::vector<std::string>& operands) {
            // leave parsing for later
            return {};
        }
    };
}
