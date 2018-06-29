#pragma once
#include "memory_cell.h"

class readonly_memory_cell : public memory_cell {

public:
    void store(byte value) override {
        throw "Cannot Store";
    }
};