#pragma once
#include "operand.h"
#include <gamekid/utils/types.h>
#include "operands/flags_reg8.h"
#include "operands/reg8.h"
#include "operands/reg16.h"
#include <gamekid/memory/memory.h>

namespace gamekid::cpu{ class operands_container;}

#include <memory>

namespace gamekid { class system; }

namespace gamekid::cpu {
    class cpu {
    private:
        system& _system;
        byte _sp_value_low;
        byte _sp_value_high;
        std::unique_ptr<operands_container> _operands;
    public:
        explicit cpu(system& system);
        
        operands::reg8 A;
        operands::reg8 B;
        operands::reg8 C;
        operands::reg8 D;
        operands::reg8 E;
        operands::flags_reg8 F;
        operands::reg8 H;
        operands::reg8 L;
        operands::reg16 AF;
        operands::reg16 BC;
        operands::reg16 DE;
        operands::reg16 HL;
        operands::reg16 SP;
        word PC;
        bool _interrupts_enabled;

        operands_container& operands();
        void enable_interrupts();
        void disable_interrupts();


        void halt() {}
        void stop() {}
        void error(){}

        memory::memory& memory();
        gamekid::system& system();

        ~cpu();
    };
}