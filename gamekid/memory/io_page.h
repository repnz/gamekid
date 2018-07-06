#pragma once
#include "page.h"
#include <gamekid/io/joypad_cell.h>
#include <array>

namespace gamekid::memory {
    class io_page : public page {
    private:
        io::joypad_cell _joypad_cell;
        std::array<cell*, 256> _cells;
    public:
        static const word io_page_memory = 0xFF00;
        io_page();
        byte load(byte offset) override;
        void store(byte offset, byte value) override;
    };
}
