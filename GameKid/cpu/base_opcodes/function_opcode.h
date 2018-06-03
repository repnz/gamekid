#pragma once
#include "GameKid/cpu/opcode.h"
#include <functional>

class function_opcode : public opcode
{
private:
    std::function<void()> _function;
public:
    function_opcode(cpu& cpu, const std::string& name, const std::vector<byte>& value, byte cycles,
        const std::function<void()>& function)
        : opcode(cpu, name, value, cycles),
          _function(function)
    {
    }

    void run() override
    {
        _function();
    }
};
