#pragma once
#include <gamekid/utils/types.h>

namespace gamekid::cpu::impl { 
    struct opcodes_struct {
        byte A;
        byte B;
        byte C;
        byte D;
        byte E;
        byte H;
        byte L;
        byte HL_mem;
        byte IMM;
    };
}