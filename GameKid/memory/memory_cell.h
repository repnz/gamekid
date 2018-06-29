#pragma once
#include <GameKid/cpu_types.h>

class memory_cell {
private:
    byte _value;
public:
    memory_cell() : _value(0){}
    memory_cell(memory_cell&&) = default;
    memory_cell& operator=(memory_cell&&) = default;
    memory_cell(const memory_cell&) = delete;
    memory_cell& operator=(const memory_cell&) = delete;
    

    virtual byte load() { return _value; }
    virtual void store(byte value) { _value = value; }
};